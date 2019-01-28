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
        public TileEditor()
        {
            InitializeComponent();
        }

        private void TileEditor_Load(object sender, EventArgs e)
        {
            XDocument configXML = XDocument.Load("data/config.xml");
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("sets").Descendants("set"))
            {
                tileSet.Items.Add(element.Attribute("name").Value);
            }
        }

        /* Add tile to config */
        private void button1_Click(object sender, EventArgs e)
        {
            if (tileName.Text == "" || tileSet.Text == "" || tileSprite.Text == "" || (tileWidth.Text == "" && tileWidth.Enabled == true) || (tileHeight.Text == "" && tileHeight.Enabled == true))
            {
                MessageBox.Show("Please enter all required information!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                if (tileSet.Text == "DEFAULT")
                {
                    MessageBox.Show("Cannot add a tile to the default sprite set!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
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

                    string newSpritePath = "data/TILES/" + tileSet.Text + "/" + Path.GetFileNameWithoutExtension(tileSprite.Text) + DateTime.Now.ToString("hhmmss") + Path.GetExtension(tileSprite.Text);
                    bool hasPathError = false;
                    if (File.Exists(newSpritePath))
                    {
                        newSpritePath = "data/TILES/" + tileSet.Text + "/" + Path.GetFileNameWithoutExtension(tileSprite.Text) + DateTime.Now.ToString("hhmmssdddmmyy") + Path.GetExtension(tileSprite.Text);
                        if (File.Exists(newSpritePath))
                        {
                            hasPathError = true;
                        }
                    }
                    if (!hasPathError)
                    {
                        //Load
                        XDocument configXML = XDocument.Load("data/config.xml");

                        //Make new tile element
                        XElement newTileParent = new XElement("tile",
                            new XAttribute("name", tileName.Text),
                            new XAttribute("set", tileSet.Text),
                            new XAttribute("sprite", newSpritePath),
                            new XAttribute("mandatory", "false"),

                            new XElement("dimensions",
                                new XAttribute("width", tileWidthString),
                                new XAttribute("heigth", tileHeightString)
                            ),
                            new XElement("valid_exits",
                                new XAttribute("left", EXIT_Left.Checked),
                                new XAttribute("right", EXIT_Right.Checked),
                                new XAttribute("up", EXIT_Up.Checked),
                                new XAttribute("down", EXIT_Down.Checked)
                            ),
                            new XElement("points_of_interest",
                                new XAttribute("computer", POI_Computer.Checked),
                                new XAttribute("door", POI_Door.Checked)
                            )
                        );
                        configXML.Element("config").Element("tile_config").Element("tiles").Add(newTileParent);

                        //Copy Sprite
                        Directory.CreateDirectory(Path.GetDirectoryName(newSpritePath));
                        File.Copy(tileSprite.Text, newSpritePath);

                        //Save
                        configXML.Save("data/config.xml");
                        MessageBox.Show("Tile created!", "Created.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        this.Close();
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
            }
        }

        private void addSet_Click(object sender, EventArgs e)
        {
            //Depreciated
        }
    }
}
