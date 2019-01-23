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
    public partial class Landing : Form
    {
        public Landing()
        {
            InitializeComponent();
        }

        private void Landing_Load(object sender, EventArgs e)
        {
            if (!File.Exists("config.xml"))
            {
                XElement configBasics = new XElement("config",
                    new XElement("tile_config",
                        new XElement("sets"),
                        new XElement("tiles")
                    ),
                    new XElement("room_config",
                        new XElement("rooms")
                    ),
                    new XElement("map_config")
                );
                configBasics.Save("config.xml");
            }
        }

        private void openTileEditor_Click(object sender, EventArgs e)
        {
            TileEditor editor = new TileEditor();
            editor.Show();
        }
    }
}
