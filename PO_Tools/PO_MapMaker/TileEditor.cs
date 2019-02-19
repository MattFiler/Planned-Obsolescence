using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Xml.Linq;

namespace PO_MapMaker
{
    public partial class TileEditor : Form
    {
        XElement importedTileNode;
        bool allowOverwrite = false;
        string currentSet = "";
        public TileEditor(XElement tileNode = null, string currentlySelectedSet = "")
        {
            importedTileNode = tileNode;
            currentSet = currentlySelectedSet;
            InitializeComponent();
        }

        XDocument configXML;
        private void TileEditor_Load(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");
            defaultSizes.Checked = true;
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("sets").Descendants("set"))
            {
                tileSet.Items.Add(element.Attribute("name").Value);
            }
            if (importedTileNode != null)
            {
                //We're editing - not creating a new tile... load existing data.
                tileName.Text = importedTileNode.Attribute("name").Value;
                tileSet.Text = importedTileNode.Attribute("set").Value;
                tileSprite.Text = importedTileNode.Attribute("sprite").Value;
                if (importedTileNode.Element("dimensions").Attribute("width").Value == "DEFAULT" &&
                    importedTileNode.Element("dimensions").Attribute("height").Value == "DEFAULT")
                {
                    tileWidth.Enabled = false;
                    tileHeight.Enabled = false;
                }
                else
                {
                    defaultSizes.Checked = false;
                    tileWidth.Text = importedTileNode.Element("dimensions").Attribute("width").Value;
                    tileHeight.Text = importedTileNode.Element("dimensions").Attribute("height").Value;
                }
                modifyCheckboxByInputData(importedTileNode.Element("valid_exits").Attribute("left").Value, EXIT_Left);
                modifyCheckboxByInputData(importedTileNode.Element("valid_exits").Attribute("right").Value, EXIT_Right);
                modifyCheckboxByInputData(importedTileNode.Element("valid_exits").Attribute("up").Value, EXIT_Up);
                modifyCheckboxByInputData(importedTileNode.Element("valid_exits").Attribute("down").Value, EXIT_Down);
                modifyCheckboxByInputData(importedTileNode.Element("points_of_interest").Attribute("computer").Value, POI_Computer);
                modifyCheckboxByInputData(importedTileNode.Element("points_of_interest").Attribute("door").Value, POI_Door);
                using (var tempPreviewImg = new Bitmap(importedTileNode.Attribute("sprite").Value))
                {
                    //Fixing file lock issue, cheers: https://stackoverflow.com/a/8701772
                    tilePreview.Image = new Bitmap(tempPreviewImg);
                }
                allowOverwrite = true; //Dangerous!
            }
            else
            {
                tileSet.SelectedItem = currentSet;
            }
        }
        void modifyCheckboxByInputData(string inputData, CheckBox checkBox)
        {
            if (inputData == "true")
            {
                checkBox.Checked = true;
            }
            else
            {
                checkBox.Checked = false;
            }
        }

        /* Add tile to config */
        private void button1_Click(object sender, EventArgs e)
        {
            if (tileName.Text == "" || 
                tileSet.Text == "" || 
                tileSprite.Text == "" || 
                (tileWidth.Text == "" && tileWidth.Enabled == true) || 
                (tileHeight.Text == "" && tileHeight.Enabled == true) ||
                (POI_Door.Checked && altSprite.Text == "") ||
                (POI_Computer.Checked && altSprite.Text == "") ||
                (POI_Computer.Checked && POI_Desc.Text ==""))
            {
                MessageBox.Show("Please enter all required information!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                if (tileSet.Text == "DEFAULT" && importedTileNode.Attribute("mandatory").Value != "true")
                {
                    MessageBox.Show("Cannot add a tile to the default sprite set!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    bool importedIsMandatory = false;
                    if (importedTileNode != null && importedTileNode.Attribute("mandatory").Value == "true")
                    {
                        importedIsMandatory = true;
                    }
                    if (importedIsMandatory && tileSet.Text != "DEFAULT")
                    {
                        MessageBox.Show("The default tile's set must be 'DEFAULT'!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                    {
                        //Handle default sizes
                        string tileWidthString = tileWidth.Text;
                        string tileHeightString = tileHeight.Text;
                        if (tileWidth.Enabled == false && tileHeight.Enabled == false)
                        {
                            tileWidthString = "DEFAULT";
                            tileHeightString = "DEFAULT";
                        }

                        //Try and generate sprite path
                        string newSpritePath = "";
                        string newAltSpritePath = "";
                        bool hasPathError = false;
                        if (allowOverwrite && tileSprite.Text.Substring(0, 10) == "data/TILES")
                        {
                            //Editing existing tile and sprite is already copied
                            newSpritePath = tileSprite.Text;
                            newAltSpritePath = altSprite.Text;
                        }
                        else
                        {
                            //Creating new tile (or importing new sprite for existing) - generate a path
                            newSpritePath = "data/TILES/" + tileSet.Text + "/" + Path.GetFileNameWithoutExtension(tileSprite.Text) + "_" + DateTime.Now.ToString("hhmmss") + Path.GetExtension(tileSprite.Text);
                            if (altSprite.Text != "")
                            {
                                newAltSpritePath = "data/TILES/" + tileSet.Text + "/" + Path.GetFileNameWithoutExtension(altSprite.Text) + "_alt_" + DateTime.Now.ToString("hhmmss") + Path.GetExtension(altSprite.Text);
                            }
                            if (File.Exists(newSpritePath) || (altSprite.Text != "" && File.Exists(newAltSpritePath)))
                            {
                                hasPathError = true;
                            }
                            if (allowOverwrite)
                            {
                                //Tidy up old file
                                File.Delete(importedTileNode.Attribute("sprite").Value);
                                if (altSprite.Text != "")
                                {
                                    File.Delete(importedTileNode.Element("points_of_interest").Attribute("alt_sprite").Value);
                                }
                            }
                        }

                        //Check for conflicts in name
                        bool hasNameConflict = false;
                        if (!allowOverwrite)
                        {
                            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("tiles").Descendants("tile"))
                            {
                                if (element.Attribute("name").Value == tileName.Text)
                                {
                                    hasNameConflict = true;
                                }
                            }
                        }

                        //Continue if no issues
                        if (!hasPathError && !hasNameConflict)
                        {
                            //Load
                            XDocument configXML = XDocument.Load("data/config.xml");

                            //Delete old node if we're editing
                            if (allowOverwrite)
                            {
                                foreach (XElement node in configXML.Element("config").Element("tile_config").Element("tiles").Elements())
                                {
                                    if (node.Attribute("name").Value == importedTileNode.Attribute("name").Value)
                                    {
                                        node.Remove();
                                        break;
                                    }
                                }
                            }

                            //Make new tile element
                            XElement newTileParent = new XElement("tile",
                                new XAttribute("name", tileName.Text),
                                new XAttribute("set", tileSet.Text),
                                new XAttribute("sprite", newSpritePath),
                                new XAttribute("mandatory", "false"),

                                new XElement("dimensions",
                                    new XAttribute("width", tileWidthString),
                                    new XAttribute("height", tileHeightString)
                                ),
                                new XElement("valid_exits",
                                    new XAttribute("left", EXIT_Left.Checked),
                                    new XAttribute("right", EXIT_Right.Checked),
                                    new XAttribute("up", EXIT_Up.Checked),
                                    new XAttribute("down", EXIT_Down.Checked)
                                ),
                                new XElement("points_of_interest",
                                    new XAttribute("computer", POI_Computer.Checked),
                                    new XAttribute("door", POI_Door.Checked),
                                    new XAttribute("description", POI_Desc.Text),
                                    new XAttribute("alt_sprite", newAltSpritePath)
                                )
                            );
                            configXML.Element("config").Element("tile_config").Element("tiles").Add(newTileParent);

                            //Copy sprite if new (might edit and not change sprite - no point copying if so)
                            if (tileSprite.Text != newSpritePath)
                            {
                                Directory.CreateDirectory(Path.GetDirectoryName(newSpritePath));
                                File.Copy(tileSprite.Text, newSpritePath);
                            }
                            if (altSprite.Text != newAltSpritePath)
                            {
                                Directory.CreateDirectory(Path.GetDirectoryName(newAltSpritePath));
                                File.Copy(altSprite.Text, newAltSpritePath);
                            }

                            //Save
                            configXML.Save("data/config.xml");
                            if (allowOverwrite)
                            {
                                MessageBox.Show("Tile edited!", "Updated.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            }
                            else
                            {
                                MessageBox.Show("Tile created!", "Created.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            }
                            this.Close();
                        }
                        else
                        {
                            if (hasPathError)
                            {
                                MessageBox.Show("An error occured while saving. Please try again.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                            else
                            {
                                MessageBox.Show("A tile with this name already exists - please enter another.", "Conflict.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                        }
                    }
                }
            }
        }

        /* Use Default Height / Width */
        private void defaultSizes_CheckedChanged(object sender, EventArgs e)
        {
            tileWidth.Enabled = !defaultSizes.Checked;
            tileWidth.Text = "";
            tileHeight.Enabled = !defaultSizes.Checked;
            tileHeight.Text = "";
        }

        /* Browse To Sprite */
        private void button1_Click_1(object sender, EventArgs e)
        {
            OpenFileDialog filePicker = new OpenFileDialog();
            filePicker.Filter = "PO Sprites (JPG,PNG)|*.JPG;*.PNG";
            if (filePicker.ShowDialog() == DialogResult.OK)
            {
                tileSprite.Text = filePicker.FileName;
                tilePreview.Image = Image.FromFile(filePicker.FileName);
            }
        }

        private void addSet_Click(object sender, EventArgs e)
        {
            //Depreciated
        }

        /* Dis-allow both checkboxes on one tile (will break stuff!) */
        private void POI_Door_CheckedChanged(object sender, EventArgs e)
        {
            poiCheckChanged(POI_Computer);
        }
        private void POI_Computer_CheckedChanged(object sender, EventArgs e)
        {
            poiCheckChanged(POI_Door);
        }
        void poiCheckChanged(CheckBox the_other_one)
        {
            if (POI_Computer.Checked && POI_Door.Checked)
            {
                the_other_one.Checked = false;
            }
            if (POI_Computer.Checked || POI_Door.Checked)
            {
                browseToAltSprite.Enabled = true;
            }
            else
            {
                browseToAltSprite.Enabled = false;
                altSprite.Text = "";
            }
            if (POI_Computer.Checked)
            {
                POI_Desc.Enabled = true;
            }
            else
            {
                POI_Desc.Enabled = false;
                POI_Desc.Text = "";
            }
        }

        /* Find alt sprite */
        private void browseToAltSprite_Click(object sender, EventArgs e)
        {
            OpenFileDialog filePicker = new OpenFileDialog();
            filePicker.Filter = "PO Sprites (JPG,PNG)|*.JPG;*.PNG";
            if (filePicker.ShowDialog() == DialogResult.OK)
            {
                altSprite.Text = filePicker.FileName;
            }
        }
    }
}
