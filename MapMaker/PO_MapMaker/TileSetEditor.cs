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
    public partial class TileSetEditor : Form
    {
        public TileSetEditor()
        {
            InitializeComponent();
        }

        /* Add tile set to config */
        private void addSet_Click(object sender, EventArgs e)
        {
            bool throwNameError = false;
            if (tileSetName.Text != "")
            { 
                //Load
                XDocument configXML = XDocument.Load("data/config.xml");

                //Check for conflicts
                foreach (XElement element in configXML.Element("config").Element("tile_config").Element("sets").Descendants("set"))
                {
                    if (element.Attribute("name").Value == tileSetName.Text)
                    {
                        throwNameError = true;
                    }
                }

                if (!throwNameError)
                {
                    //Create new set
                    XElement newSet = new XElement("set",
                        new XAttribute("name", tileSetName.Text)
                    );
                    configXML.Element("config").Element("tile_config").Element("sets").Add(newSet);

                    //Save
                    configXML.Save("data/config.xml");
                    MessageBox.Show("Tile set created!", "Created.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    this.Close();
                }
                else
                {
                    MessageBox.Show("A tile set with this name already exists!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Please enter a name for the tile set!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
