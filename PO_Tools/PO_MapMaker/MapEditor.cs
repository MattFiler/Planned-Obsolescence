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
        XElement importedMap;
        public MapEditor(XElement mapNode = null)
        {
            importedMap = mapNode;
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
                    mapWidth.Text = element.Attribute("width").Value;
                    mapHeight.Text = element.Attribute("height").Value;
                }
            }
            mapWidth.Enabled = false;
            mapHeight.Enabled = false;
            defaultSizes.Checked = true;
            
            //See if we're importing or starting fresh
            if (importedMap != null)
            {
                //Set description
                mapDescription.Text = importedMap.Attribute("name").Value;

                //Set correct width/height (or tick default if that is the case)
                int new_map_height = Convert.ToInt32(importedMap.Attribute("width").Value);
                int new_map_width = Convert.ToInt32(importedMap.Attribute("height").Value);
                if (new_map_width == mapHeight.Value && new_map_height == mapWidth.Value)
                {
                    if (importedMap.Attribute("mandatory").Value != "true")
                    {
                        defaultSizes.Checked = true;
                        mapHeight.ReadOnly = true;
                        mapWidth.ReadOnly = true;
                    }
                    else
                    {
                        defaultSizes.Checked = false;
                        mapHeight.ReadOnly = false;
                        mapWidth.ReadOnly = false;
                    }
                }
                else
                {
                    defaultSizes.Checked = false;
                    mapHeight.ReadOnly = false;
                    mapWidth.ReadOnly = false;
                    mapHeight.Value = new_map_width;
                    mapWidth.Value = new_map_height;
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
        string[] selectedRooms = null;
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
                width = Convert.ToInt32(mapWidth.Text);
                height = Convert.ToInt32(mapHeight.Text);
            }

            //Remove existing inputs from form
            foreach (ComboBox dropdown in comboBoxes)
            {
                Controls.Remove(dropdown);
            }
            comboBoxes.Clear();

            //Get all rooms to load into dropdowns
            List<string> mapRoomList = new List<string>();
            foreach (XElement element in configXML.Element("config").Element("room_config").Element("rooms").Descendants("room"))
            {
                mapRoomList.Add(element.Attribute("name").Value);
            }

            //Create inputs
            positional_x = 0;
            positional_y = 0;
            for (int i = 0; i < (width * height); i++)
            {
                int height_index = Convert.ToInt32(i / width);
                int width_index = Convert.ToInt32(i - (width * height_index));
                populateInputs(width_index, height_index, i, mapRoomList, firstLoad);
            }

            //Add new inputs to form and store selections
            selectedRooms = new string[width * height];
            foreach (ComboBox dropdown in comboBoxes)
            {
                Controls.Add(dropdown);
                if (dropdown.SelectedIndex != -1)
                {
                    selectedRooms[Convert.ToInt32(dropdown.Name.Split('_')[1])] = dropdown.Items[dropdown.SelectedIndex].ToString();
                }
            }

            //Resize window
            Size = new Size(positional_x + 90, positional_y + 110);

            //Resize and reposition inputs
            mapDescription.Size = new Size(positional_x + 60, mapDescription.Size.Height);
            refreshMap.Size = new Size(positional_x + 60, refreshMap.Size.Height);
            saveMap.Size = new Size(positional_x + 60, saveMap.Size.Height);
            saveMap.Location = new Point(12, positional_y + 40);
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
            dropdown.Name = "roomNameSelect_" + index.ToString();
            dropdown.Size = new Size(75, 21);
            foreach (string tile in tileList)
            {
                dropdown.Items.Add(tile);
            }
            if (dropdown.Items.Count > 0)
            {
                dropdown.SelectedIndex = 0; //Should really never fail this, but it's possible.
            }
            if (importedMap != null && firstLoad)
            {
                //Load imported settings
                dropdown.SelectedItem = importedMap.Elements("room").ElementAt(index).Attribute("name").Value;
            }
            dropdown.SelectedIndexChanged += new EventHandler(updateTilePreview);
            comboBoxes.Add(dropdown);
        }

        /* Remember Selection */
        private void updateTilePreview(object sender, EventArgs e)
        {
            ComboBox dropdown = (ComboBox)sender;
            string object_id = dropdown.Name.Split('_')[1];
            selectedRooms[Convert.ToInt32(object_id)] = dropdown.Items[dropdown.SelectedIndex].ToString();
        }

        /* Reload GUI */
        private void refreshRoom_Click(object sender, EventArgs e)
        {
            refreshGUI();
        }

        /* Enable/Disable Default Useage */
        private void defaultSizes_CheckedChanged(object sender, EventArgs e)
        {
            mapWidth.Enabled = !defaultSizes.Checked;
            mapHeight.Enabled = !defaultSizes.Checked;
        }

        /* Save */
        private void saveRoom_Click(object sender, EventArgs e)
        {
            if (mapDescription.Text != "" && mapWidth.Value != 0 && mapHeight.Value != 0 && selectedRooms.Length == mapWidth.Value * mapHeight.Value)
            {
                //Check for name conflicts
                bool hasNameConflict = false;
                foreach (XElement element in configXML.Element("config").Element("map_config").Descendants("map"))
                {
                    if (element.Attribute("name").Value == mapDescription.Text)
                    {
                        if (importedMap != null)
                        {
                            if (element.Attribute("mandatory").Value == "true" && mapDescription.Text != "DEFAULT")
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
                    if (importedMap != null)
                    {
                        if (importedMap.Attribute("mandatory").Value == "true")
                        {
                            mandatory_text = "true";
                        }
                    }
                    XElement mapRoomList = new XElement("map", new XAttribute("name", mapDescription.Text), new XAttribute("mandatory", mandatory_text), new XAttribute("width", mapWidth.Text), new XAttribute("height", mapHeight.Text));
                    foreach (string tile in selectedRooms)
                    {
                        mapRoomList.Add(new XElement("room", new XAttribute("name", tile)));
                    }
                    configXML.Element("config").Element("map_config").Add(mapRoomList);
                    configXML.Save("data/config.xml");

                    if (importedMap != null)
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
                    if (importedMap != null)
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
                if (mapDescription.Text == "")
                {
                    MessageBox.Show("Please enter a map description.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    if (selectedRooms.Length != mapWidth.Value * mapHeight.Value)
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
