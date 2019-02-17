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
    public partial class MapEditor : Form
    {
        XElement importedRoom;
        public MapEditor(XElement tileNode = null)
        {
            importedRoom = tileNode;
            InitializeComponent();
        }

        XDocument configXML;
        private void MapEditor_Load_1(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");

            //Get default width/height
            foreach (XElement element in configXML.Element("config").Element("map_config").Descendants("map"))
            {
                if (element.Attribute("name").Value == "DEFAULT")
                {
                    roomWidth.Text = element.Attribute("width").Value;
                    roomHeight.Text = element.Attribute("height").Value;
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

                //Set correct width/height (or tick default if that is the case)
                int new_room_width = Convert.ToInt32(importedRoom.Attribute("width").Value);
                int new_room_height = Convert.ToInt32(importedRoom.Attribute("height").Value);
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
                foreach (XElement element in configXML.Element("config").Element("map_config").Descendants("map"))
                {
                    if (element.Attribute("name").Value == "DEFAULT")
                    {
                        width = Convert.ToInt32(element.Attribute("width").Value);
                        height = Convert.ToInt32(element.Attribute("height").Value);
                    }
                }
            }
            else
            {
                width = Convert.ToInt32(roomWidth.Text);
                height = Convert.ToInt32(roomHeight.Text);
            }

            //Remove existing inputs from form
            foreach (ComboBox dropdown in comboBoxes)
            {
                Controls.Remove(dropdown);
            }
            comboBoxes.Clear();

            //Get all rooms to load into dropdowns
            List<string> tileList = new List<string>();
            foreach (XElement element in configXML.Element("config").Element("room_config").Element("rooms").Descendants("room"))
            {
                tileList.Add(element.Attribute("name").Value);
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
            selectedTiles = new string[width * height];
            foreach (ComboBox dropdown in comboBoxes)
            {
                Controls.Add(dropdown);
                if (dropdown.SelectedIndex != -1)
                {
                    selectedTiles[Convert.ToInt32(dropdown.Name.Split('_')[1])] = dropdown.Items[dropdown.SelectedIndex].ToString();
                }
            }

            //Resize window
            Size = new Size(positional_x + 90, positional_y + 110);

            //Resize and reposition inputs
            roomName.Size = new Size(positional_x + 60, roomName.Size.Height);
            refreshRoom.Size = new Size(positional_x + 60, refreshRoom.Size.Height);
            saveRoom.Size = new Size(positional_x + 60, saveRoom.Size.Height);
            saveRoom.Location = new Point(12, positional_y + 40);
        }
        void populateInputs(int width_index, int height_index, int index, List<string> tileList, bool firstLoad)
        {
            //Update sizes/positions
            positional_x = (width_index * 80) + 10;
            positional_y = (height_index * 30) + 140;

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
                dropdown.SelectedItem = importedRoom.Elements("room").ElementAt(index).Attribute("name").Value;
            }
            dropdown.SelectedIndexChanged += new EventHandler(updateTilePreview);
            comboBoxes.Add(dropdown);
        }

        /* Remember Selection */
        private void updateTilePreview(object sender, EventArgs e)
        {
            ComboBox dropdown = (ComboBox)sender;
            string object_id = dropdown.Name.Split('_')[1];
            selectedTiles[Convert.ToInt32(object_id)] = dropdown.Items[dropdown.SelectedIndex].ToString();
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
                foreach (XElement element in configXML.Element("config").Element("map_config").Descendants("map"))
                {
                    if (element.Attribute("name").Value == roomName.Text)
                    {
                        if (importedRoom != null)
                        {
                            if (element.Attribute("mandatory").Value == "true" && roomName.Text != "DEFAULT")
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
                    XElement roomTileList = new XElement("map", new XAttribute("name", roomName.Text), new XAttribute("mandatory", mandatory_text), new XAttribute("width", roomWidth.Text), new XAttribute("height", roomHeight.Text));
                    foreach (string tile in selectedTiles)
                    {
                        roomTileList.Add(new XElement("room", new XAttribute("name", tile)));
                    }
                    configXML.Element("config").Element("map_config").Add(roomTileList);
                    configXML.Save("data/config.xml");

                    if (importedRoom != null)
                    {
                        MessageBox.Show("Map edited!", "Created.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    else
                    {
                        MessageBox.Show("Map created!", "Created.", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
                        MessageBox.Show("A map with this description already exists.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
            else
            {
                if (roomName.Text == "")
                {
                    MessageBox.Show("Please enter a map description.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
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


        private void MapEditor_Load(object sender, EventArgs e)
        {
            //Depreciated
        }
    }
}
