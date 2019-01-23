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
        }

        /* Add tile to config */
        private void button1_Click(object sender, EventArgs e)
        {
            //Load
            XDocument configXML = XDocument.Load("config.xml");

            /* NEW TILE */
            XElement newTileParent = new XElement("tile",
                new XAttribute("set", ""),
                new XAttribute("sprite", ""),

                new XElement("dimensions",
                    new XAttribute("width", ""),
                    new XAttribute("heigth", "")
                ),
                new XElement("valid_exits",
                    new XAttribute("left", ""),
                    new XAttribute("right", ""),
                    new XAttribute("up", ""),
                    new XAttribute("down", "")
                ),
                new XElement("points_of_interest",
                    new XAttribute("computer", ""),
                    new XAttribute("door", "")
                )
            );
            configXML.Element("config").Element("tile_config").Element("tiles").Add(newTileParent);
            
            //Save
            configXML.Save("config.xml");
        }

        /* Add tile set to config */
        private void addSet_Click(object sender, EventArgs e)
        {
            //Load
            XDocument configXML = XDocument.Load("config.xml");
            
            /* NEW SET */
            XElement newSet = new XElement("set",
                new XAttribute("name", "")
            );
            configXML.Element("config").Element("tile_config").Element("sets").Add(newSet);

            //Save
            configXML.Save("config.xml");
        }
    }
}
