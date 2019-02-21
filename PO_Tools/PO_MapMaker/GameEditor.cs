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
    public partial class GameEditor : Form
    {
        public GameEditor()
        {
            InitializeComponent();
        }

        /* Load existing config */
        XDocument configXML;
        private void GameEditor_Load(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");

            //Set existing options
            GameHeight.Text = configXML.Element("config").Element("game_config").Element("resolution").Attribute("height").Value;
            GameWidth.Text = configXML.Element("config").Element("game_config").Element("resolution").Attribute("width").Value;
            if (configXML.Element("config").Element("game_config").Element("debug").Attribute("enabled").Value == "true")
            {
                EnableDebug.Checked = true;
            }
            else
            {
                EnableDebug.Checked = false;
            }
        }

        /* Save changes */
        private void saveGameAttrs_Click(object sender, EventArgs e)
        {
            if (GameWidth.Text != "" && GameHeight.Text != "")
            {
                //Update config
                configXML.Element("config").Element("game_config").Element("resolution").Attribute("height").Value = GameHeight.Text;
                configXML.Element("config").Element("game_config").Element("resolution").Attribute("width").Value = GameWidth.Text;
                configXML.Element("config").Element("game_config").Element("debug").Attribute("enabled").Value = EnableDebug.Checked.ToString().ToLower();

                //Save
                configXML.Save("data/config.xml");
                MessageBox.Show("Game configuration saved!", "Created.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.Close();
            }
            else
            {
                MessageBox.Show("Please enter both resolution sizes!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
