using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace PO_MapMaker
{
    public partial class RoomEditor : Form
    {
        XElement importedRoom;
        public RoomEditor(XElement tileNode = null)
        {
            importedRoom = tileNode;
            InitializeComponent();
        }

        XDocument configXML;
        Bitmap defaultImage;
        private void RoomEditor_Load(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");

            //Load sets
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("sets").Descendants("set"))
            {
                tileSet.Items.Add(element.Attribute("name").Value);
            }
            tileSet.SelectedIndex = 0;

            //Get default sprite
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("tiles").Descendants("tile"))
            {
                if (element.Attribute("name").Value == "DEFAULT")
                {
                    using (var tempPreviewImg = new Bitmap(element.Attribute("sprite").Value))
                    {
                        defaultImage = new Bitmap(tempPreviewImg);
                    }
                }
            }

            //Get default width/height
            foreach (XElement element in configXML.Element("config").Element("room_config").Element("rooms").Descendants("room"))
            {
                if (element.Attribute("name").Value == "DEFAULT")
                {
                    roomWidth.Text = element.Element("tiles").Attribute("width").Value;
                    roomHeight.Text = element.Element("tiles").Attribute("height").Value;
                }
            }
            roomWidth.Enabled = false;
            roomHeight.Enabled = false;
            defaultSizes.Checked = true;

            //See if we're importing or starting fresh
            if (importedRoom != null)
            {
                //Set description
                roomName.Text = importedRoom.Attribute("name").Value;

                //Select correct tileset
                foreach (XElement element in configXML.Element("config").Element("tile_config").Element("tiles").Descendants("tile"))
                {
                    if (element.Attribute("name").Value == importedRoom.Element("tiles").Elements("tile").First().Attribute("name").Value)
                    {
                        tileSet.SelectedItem = element.Attribute("set").Value;
                    }
                }

                //Set correct width/height (or tick default if that is the case)
                int new_room_width = Convert.ToInt32(importedRoom.Element("tiles").Attribute("width").Value);
                int new_room_height = Convert.ToInt32(importedRoom.Element("tiles").Attribute("height").Value);
                if (new_room_height == roomHeight.Value && new_room_width == roomWidth.Value)
                {
                    if (importedRoom.Attribute("mandatory").Value != "true")
                    {
                        defaultSizes.Checked = true;
                        roomHeight.ReadOnly = true;
                        roomWidth.ReadOnly = true;
                    }
                    else
                    {
                        defaultSizes.Checked = false;
                        roomHeight.ReadOnly = false;
                        roomWidth.ReadOnly = false;
                    }
                }
                else
                {
                    defaultSizes.Checked = false;
                    roomHeight.ReadOnly = false;
                    roomWidth.ReadOnly = false;
                    roomHeight.Value = new_room_height;
                    roomWidth.Value = new_room_width;
                }

                //Load in the imported data
                refreshGUI(true);
            }
            else
            {
                //Load in default data
                refreshGUI();
            }
        }

        /* Make the Editor GUI */
        List<ComboBox> comboBoxes = new List<ComboBox>();
        List<PictureBox> previewBoxes = new List<PictureBox>();
        string[] selectedTiles = null;
        int positional_x = 0;
        int positional_y = 0;
        void refreshGUI(bool firstLoad = false)
        {
            int width = 0;
            int height = 0;
            if (defaultSizes.Checked)
            {
                //Get default width/height if requested
                foreach (XElement element in configXML.Element("config").Element("room_config").Element("rooms").Descendants("room"))
                {
                    if (element.Attribute("name").Value == "DEFAULT")
                    {
                        width = Convert.ToInt32(element.Element("tiles").Attribute("width").Value);
                        height = Convert.ToInt32(element.Element("tiles").Attribute("height").Value);
                    }
                }
            }
            else
            {
                width = Convert.ToInt32(roomWidth.Text);
                height = Convert.ToInt32(roomHeight.Text);
            }
            string selectedTileSet = tileSet.Items[tileSet.SelectedIndex].ToString();

            //Update default preview image
            foreach (XElement tile in configXML.Element("config").Element("tile_config").Element("tiles").Elements("tile"))
            {
                if (tile.Attribute("set").Value == selectedTileSet)
                {
                    using (var tempPreviewImg = new Bitmap(tile.Attribute("sprite").Value))
                    {
                        defaultImage = new Bitmap(tempPreviewImg);
                    }
                    break;
                }
            }

            //Remove existing inputs from form
            foreach (ComboBox dropdown in comboBoxes)
            {
                Controls.Remove(dropdown);
            }
            comboBoxes.Clear();
            foreach (PictureBox preview in previewBoxes)
            {
                Controls.Remove(preview);
            }
            previewBoxes.Clear();

            //Get tiles in selected set
            List<string> tileList = new List<string>();
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("tiles").Descendants("tile"))
            {
                if (element.Attribute("set").Value == selectedTileSet)
                {
                    tileList.Add(element.Attribute("name").Value);
                }
            }

            //Create inputs
            positional_x = 0;
            positional_y = 0;
            for (int i = 0; i < (width * height); i++)
            {
                int height_index = Convert.ToInt32(i / width);
                int width_index = Convert.ToInt32(i - (width * height_index));
                populateInputs(width_index, height_index, i, tileList, firstLoad);
            }

            //Add new inputs to form and store selections
            selectedTiles = new string[width*height];
            foreach (ComboBox dropdown in comboBoxes)
            {
                Controls.Add(dropdown);
                if (dropdown.SelectedIndex != -1)
                {
                    selectedTiles[Convert.ToInt32(dropdown.Name.Split('_')[1])] = dropdown.Items[dropdown.SelectedIndex].ToString();
                }
            }
            foreach (PictureBox preview in previewBoxes)
            {
                Controls.Add(preview);
            }

            //Resize window
            Size = new Size(positional_x + 100, positional_y + 190);

            //Resize and reposition inputs
            roomName.Size = new Size(positional_x + 60, roomName.Size.Height);
            tileSet.Size = new Size(positional_x + 60, tileSet.Size.Height);
            refreshRoom.Size = new Size(positional_x + 60, refreshRoom.Size.Height);
            saveRoom.Size = new Size(positional_x + 60, saveRoom.Size.Height);
            saveRoom.Location = new Point(12, positional_y + 110);
        }
        void populateInputs(int width_index, int height_index, int index, List<string> tileList, bool firstLoad)
        {
            //Update sizes/positions
            positional_x = (width_index * 80) + 10;
            positional_y = (height_index * 100) + 180;

            //Dropdown
            ComboBox dropdown = new ComboBox();
            dropdown.DropDownStyle = ComboBoxStyle.DropDownList;
            dropdown.FormattingEnabled = true;
            dropdown.Location = new Point(positional_x, positional_y);
            dropdown.Name = "tileNameSelect_" + index.ToString();
            dropdown.Size = new Size(75, 21);
            foreach (string tile in tileList)
            {
                dropdown.Items.Add(tile);
            }
            if (dropdown.Items.Count > 0)
            {
                dropdown.SelectedIndex = 0; //Should really never fail this, but it's possible.
            }
            if (importedRoom != null && firstLoad)
            {
                //Load imported settings
                dropdown.SelectedItem = importedRoom.Element("tiles").Elements("tile").ElementAt(index).Attribute("name").Value;
                foreach (XElement tile_data in configXML.Element("config").Element("tile_config").Element("tiles").Descendants("tile"))
                {
                    if (tile_data.Attribute("name").Value == dropdown.SelectedItem.ToString())
                    {
                        using (var tempPreviewImg = new Bitmap(tile_data.Attribute("sprite").Value))
                        {
                            defaultImage = new Bitmap(tempPreviewImg);
                        }
                    }
                }
            }
            dropdown.SelectedIndexChanged += new EventHandler(updateTilePreview);
            comboBoxes.Add(dropdown);

            //Preview box
            PictureBox preview = new PictureBox();
            preview.Location = new Point(positional_x, positional_y + 21);
            preview.Name = "tilePreview_" + index.ToString();
            preview.Size = new Size(75, 75);
            preview.SizeMode = PictureBoxSizeMode.StretchImage;
            if (dropdown.Items.Count > 0)
            {
                preview.Image = defaultImage;
            }
            else
            {
                preview.Image = null; //Again, nice if we couldn't get here - but we can.
            }
            previewBoxes.Add(preview);
        }

        /* Update Preview & Remember Selection */
        private void updateTilePreview(object sender, EventArgs e)
        {
            ComboBox dropdown = (ComboBox)sender;
            string object_id = dropdown.Name.Split('_')[1];

            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("tiles").Descendants("tile"))
            {
                if (element.Attribute("name").Value == dropdown.Items[dropdown.SelectedIndex].ToString())
                {
                    foreach (PictureBox preview in previewBoxes)
                    {
                        if (preview.Name == "tilePreview_" + object_id)
                        {
                            using (var tempPreviewImg = new Bitmap(element.Attribute("sprite").Value))
                            {
                                preview.Image = new Bitmap(tempPreviewImg);
                                selectedTiles[Convert.ToInt32(object_id)] = dropdown.Items[dropdown.SelectedIndex].ToString();
                            }
                        }
                    }
                }
            }
        }

        /* Reload GUI */
        private void refreshRoom_Click(object sender, EventArgs e)
        {
            refreshGUI();
        }

        /* Enable/Disable Default Useage */
        private void defaultSizes_CheckedChanged(object sender, EventArgs e)
        {
            roomWidth.Enabled = !defaultSizes.Checked;
            roomHeight.Enabled = !defaultSizes.Checked;
        }

        /* Save */
        private void saveRoom_Click(object sender, EventArgs e)
        {
            if (roomName.Text != "" && roomWidth.Value != 0 && roomHeight.Value != 0 && selectedTiles.Length == roomWidth.Value * roomHeight.Value)
            {
                //Check for name conflicts
                bool hasNameConflict = false;
                foreach (XElement element in configXML.Element("config").Element("room_config").Element("rooms").Descendants("room"))
                {
                    if (element.Attribute("name").Value == roomName.Text)
                    {
                        if (importedRoom != null)
                        {
                            if (element.Attribute("mandatory").Value == "true" && (roomName.Text != "DEFAULT" || tileSet.SelectedItem.ToString() != "DEFAULT"))
                            {
                                //Default (mandatory) configs must keep these settings... throw a conflict.
                                hasNameConflict = true;
                            }
                            //We are editing (replacing) an old roomset - delete it first!
                            element.Remove();
                        }
                        else
                        {
                            //We are conflicting with an existing roomset - stop!
                            hasNameConflict = true;
                        }
                        break;
                    }
                }
            
                if (!hasNameConflict)
                {
                    //Save
                    string mandatory_text = "false";
                    if (importedRoom != null)
                    {
                        if (importedRoom.Attribute("mandatory").Value == "true")
                        {
                            mandatory_text = "true";
                        }
                    }
                    XElement roomTileList = new XElement("room", new XAttribute("name", roomName.Text), new XAttribute("mandatory", mandatory_text), new XElement("tiles", new XAttribute("width", roomWidth.Text), new XAttribute("height", roomHeight.Text)));
                    foreach (string tile in selectedTiles)
                    {
                        roomTileList.Element("tiles").Add(new XElement("tile", new XAttribute("name", tile)));
                    }
                    configXML.Element("config").Element("room_config").Element("rooms").Add(roomTileList);
                    configXML.Save("data/config.xml");

                    if (importedRoom != null)
                    {
                        MessageBox.Show("Room edited!", "Created.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    else
                    {
                        MessageBox.Show("Room created!", "Created.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    this.Close();
                }
                else
                {
                    if (importedRoom != null)
                    {
                        MessageBox.Show("Default configurations must keep the same name and tileset.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                    {
                        MessageBox.Show("A room with this description already exists.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
            else
            {
                if (roomName.Text == "")
                {
                    MessageBox.Show("Please enter a room description.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    if (selectedTiles.Length != roomWidth.Value * roomHeight.Value)
                    {
                        MessageBox.Show("You must refresh the form when changing room width/height before saving.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                    {
                        MessageBox.Show("Room width/height must be bigger than zero.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }


        private void tileSet_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Depreciated
        }
        private void roomHeight_ValueChanged(object sender, EventArgs e)
        {
            //Depreciated
        }
        private void roomWidth_ValueChanged(object sender, EventArgs e)
        {
            //Depreciated
        }
        private void roomWidth_TextChanged(object sender, EventArgs e)
        {
            //Depreciated
        }
        private void roomHeight_TextChanged(object sender, EventArgs e)
        {
            //Depreciated
        }
    }
}
