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
    public partial class KeybindEditor : Form
    {
        public KeybindEditor()
        {
            InitializeComponent();
        }

        XDocument configXML;
        List<TextBox> textboxes = new List<TextBox>();
        List<ComboBox> dropdowns = new List<ComboBox>();
        int y_offset = 70;
        private void KeybindEditor_Load(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");

            //Load existing config
            foreach (XElement keybind in configXML.Element("config").Element("game_config").Element("keybinds").Descendants("bind"))
            {
                addNewInputs(keybind.Attribute("action").Value, keybind.Attribute("key").Value);
            }

            if (y_offset == 70)
            {
                //Should never get here, but adds a default keybind if we have none.
                addNewInputs();
            }
        }

        /* Add Input */
        private void button1_Click(object sender, EventArgs e)
        {
            addNewInputs();
        }

        /* Remove Input */
        private void button2_Click(object sender, EventArgs e)
        {
            if (textboxes.Count() > 1)
            {
                Controls.Remove(textboxes[textboxes.Count() - 1]);
                Controls.Remove(dropdowns[dropdowns.Count() - 1]);
                textboxes.Remove(textboxes[textboxes.Count() - 1]);
                dropdowns.Remove(dropdowns[dropdowns.Count() - 1]);
                y_offset -= 25;
                resizeWindow();
            }
            else
            {
                MessageBox.Show("You must have at least one keybind!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /* Save Keybinds */
        private void saveKeybinds_Click(object sender, EventArgs e)
        {
            //Remove existing binds
            configXML.Element("config").Element("game_config").Element("keybinds").Remove();
            configXML.Element("config").Element("game_config").Add(new XElement("keybinds"));

            //Add new binds
            bool encounteredError = false;
            for (int i=0; i<textboxes.Count(); i++)
            {
                if (dropdowns[i].SelectedIndex == -1 || textboxes[i].Text == "")
                {
                    MessageBox.Show("Please fill out all added keybinds!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    configXML = XDocument.Load("data/config.xml");
                    encounteredError = true;
                    break;
                }
                else
                {
                    configXML.Element("config").Element("game_config").Element("keybinds").Add(new XElement("bind", new XAttribute("key", dropdowns[i].Items[dropdowns[i].SelectedIndex]), new XAttribute("action", textboxes[i].Text)));
                }
            }

            //If no errors, save
            if (!encounteredError)
            {
                configXML.Save("data/config.xml");
                MessageBox.Show("Keybinds saved!", "Saved.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.Close();
            }
        }

        /* Add new keybind inputs */
        void addNewInputs(string keybind_name = "", string keybind_selected = "")
        {
            //New textbox
            TextBox newTextBox = new TextBox();
            newTextBox.Name = "ActionName_" + textboxes.Count();
            newTextBox.Size = new Size(243, 20);
            newTextBox.Location = new Point(12, y_offset);
            newTextBox.Text = keybind_name;
            textboxes.Add(newTextBox);
            Controls.Add(newTextBox);

            //New dropdown
            ComboBox newDropdown = new ComboBox();
            newDropdown.Name = "InputName_" + dropdowns.Count();
            newDropdown.Size = new Size(158, 21);
            newDropdown.Location = new Point(264, y_offset);
            newDropdown.DropDownStyle = ComboBoxStyle.DropDownList;
            newDropdown.Items.AddRange(new object[] {
            "KEY_A","KEY_B","KEY_C","KEY_D","KEY_E","KEY_F","KEY_G","KEY_H","KEY_I","KEY_J","KEY_K","KEY_L","KEY_M",
            "KEY_N","KEY_O","KEY_P","KEY_Q","KEY_R","KEY_S","KEY_T","KEY_U","KEY_V","KEY_W","KEY_X","KEY_Y","KEY_Z",
            "KEY_SPACE","KEY_APOSTROPHE","KEY_COMMA","KEY_MINUS","KEY_PERIOD","KEY_SLASH","KEY_SEMICOLON","KEY_EQUAL",
            "KEY_0","KEY_1","KEY_2","KEY_3","KEY_4","KEY_5","KEY_6","KEY_7","KEY_8","KEY_9",
            "KEY_ESCAPE","KEY_ENTER","KEY_TAB","KEY_BACKSPACE","KEY_DELETE","KEY_RIGHT","KEY_LEFT","KEY_DOWN","KEY_UP"});
            newDropdown.SelectedItem = keybind_selected;
            dropdowns.Add(newDropdown);
            Controls.Add(newDropdown);

            y_offset += 25;
            resizeWindow();
        }

        /* Resize Window */
        void resizeWindow()
        {
            Size = new Size(449, y_offset + 90);
            saveKeybinds.Location = new Point(12, y_offset + 15);
        }
    }
}
