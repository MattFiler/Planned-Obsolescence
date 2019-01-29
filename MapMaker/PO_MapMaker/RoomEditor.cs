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
        public RoomEditor()
        {
            InitializeComponent();
        }

        XDocument configXML;
        private void RoomEditor_Load(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("sets").Descendants("set"))
            {
                tileSet.Items.Add(element.Attribute("name").Value);
            }
            tileSet.SelectedIndex = 0;
        }

        /* Make the Editor GUI */
        List<ComboBox> comboBoxes = new List<ComboBox>();
        List<PictureBox> previewBoxes = new List<PictureBox>();
        int positional_x = 0;
        int positional_y = 0;
        void refreshGUI()
        {
            int width = 0;
            int height = 0;
            if (defaultSizes.Checked)
            {
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
            for (int i=0; i<(width*height); i++)
            {
                int height_index = Convert.ToInt32(i / width);
                int width_index = Convert.ToInt32(i - (width * height_index));
                populateInputs(width_index, height_index, i, tileList);
            }

            //Add new inputs to form
            foreach (ComboBox dropdown in comboBoxes)
            {
                Controls.Add(dropdown);
            }
            foreach (PictureBox preview in previewBoxes)
            {
                Controls.Add(preview);
            }

            //Resize window
            Size = new Size(positional_x + 100, positional_y + 180);
        }
        void populateInputs(int width_index, int height_index, int index, List<string> tileList)
        {
            //Update sizes/positions
            positional_x = (width_index * 100) + 10;
            positional_y = (height_index * 100) + 10;

            //Dropdown
            ComboBox dropdown = new ComboBox();
            dropdown.DropDownStyle = ComboBoxStyle.DropDownList;
            dropdown.FormattingEnabled = true;
            dropdown.Location = new Point(positional_x, positional_y);
            dropdown.Name = "tileNameSelect" + index.ToString();
            dropdown.Size = new Size(75, 21);
            foreach (string tile in tileList)
            {
                dropdown.Items.Add(tile);
            }
            comboBoxes.Add(dropdown);

            //Preview box
            PictureBox preview = new PictureBox();
            preview.Location = new Point(positional_x, positional_y + 21);
            preview.Name = "tilePreview" + index.ToString();
            preview.Size = new Size(75, 75);
            preview.SizeMode = PictureBoxSizeMode.StretchImage;
            preview.Image = Image.FromFile("D:/Pictures/783.png");
            previewBoxes.Add(preview);
        }

        /* Reload GUI for new input data */
        private void tileSet_SelectedIndexChanged(object sender, EventArgs e)
        {
            refreshGUI();
        }
        private void roomWidth_TextChanged(object sender, EventArgs e)
        {
            refreshGUI();
        }
        private void roomHeight_TextChanged(object sender, EventArgs e)
        {
            refreshGUI();
        }

        /* Enable/Disable Default Useage */
        private void defaultSizes_CheckedChanged(object sender, EventArgs e)
        {
            roomWidth.Enabled = !defaultSizes.Checked;
            roomHeight.Enabled = !defaultSizes.Checked;
        }
    }
}
