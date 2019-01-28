using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace PO_MapMaker
{
    public partial class TileList : Form
    {
        public TileList()
        {
            InitializeComponent();
        }

        XDocument configXML;
        private void TileList_Load(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");

            loadTileSets();
            loadTiles();
        }

        /* Load / Clear Tile List */
        void loadTiles(string set = "DEFAULT")
        {
            clearTiles();
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("tiles").Descendants("tile"))
            {
                if (element.Attribute("set").Value == set)
                {
                    listTile.Items.Add(element.Attribute("name").Value);
                }
            }
        }
        void clearTiles()
        {
            listTile.Items.Clear();
        }

        /* Load / Clear Tile Set List */
        void loadTileSets()
        {
            clearTileSets();
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("sets").Descendants("set"))
            {
                listTileSet.Items.Add(element.Attribute("name").Value);
            }
        }
        void clearTileSets()
        {
            listTileSet.Items.Clear();
        }

        /* Refresh All */
        void refreshAllLists(object sender, FormClosedEventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");
            loadTiles(getSelectedTileSet());
            loadTileSets();
        }

        /* Get Selected Tile/Set */
        string getSelectedTile()
        {
            if (listTile.SelectedIndex == -1)
            {
                return "DEFAULT";
            }
            return listTile.Items[listTile.SelectedIndex].ToString();
        }
        string getSelectedTileSet()
        {
            if (listTileSet.SelectedIndex == -1)
            {
                return "DEFAULT";
            }
            return listTileSet.Items[listTileSet.SelectedIndex].ToString();
        }

        /* Get Nodes By Name (Tile/Set) */
        XElement getTileNodeByName(string name)
        {
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("tiles").Descendants("tile"))
            {
                if (element.Attribute("name").Value == name)
                {
                    return element;
                }
            }
            return null;
        }
        XElement getTileSetNodeByName(string name)
        {
            foreach (XElement element in configXML.Element("config").Element("tile_config").Element("sets").Descendants("set"))
            {
                if (element.Attribute("name").Value == name)
                {
                    return element;
                }
            }
            return null;
        }

        /* Open Set Editor */
        private void newTileSet_Click(object sender, EventArgs e)
        {
            TileSetEditor setEditor = new TileSetEditor();
            setEditor.Show();
            setEditor.FormClosed += new FormClosedEventHandler(refreshAllLists);
        }

        /* Open Tile Editor */
        private void newTile_Click(object sender, EventArgs e)
        {
            TileEditor tileEditor = new TileEditor(null, getSelectedTileSet());
            tileEditor.Show();
            tileEditor.FormClosed += new FormClosedEventHandler(refreshAllLists);
        }

        /* Load Selected Tile Set */
        private void loadSpriteSet_Click(object sender, EventArgs e)
        {
            loadTiles(getSelectedTileSet());
        }

        /* Delete Selected Tile Set */
        private void deleteTileSet_Click(object sender, EventArgs e)
        {
            if (getSelectedTileSet() == "DEFAULT")
            {
                MessageBox.Show("Cannot delete the default tile set!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                var confirmation = MessageBox.Show("Are you sure?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (confirmation == DialogResult.Yes)
                {
                    //Only deleting set from list, not its tiles - they can basically be recovered if the set name is added back in.
                    getTileSetNodeByName(getSelectedTileSet()).Remove();
                    configXML.Save("data/config.xml");
                    MessageBox.Show("Tile set deleted!", "Deleted.", MessageBoxButtons.OK, MessageBoxIcon.Information);

                    loadTiles();
                    loadTileSets();
                }
            }
        }

        /* Delete Selected Tile */
        private void deleteTile_Click(object sender, EventArgs e)
        {
            if (getTileNodeByName(getSelectedTile()).Attribute("mandatory").Value == "true")
            {
                MessageBox.Show("Cannot delete the default tile!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                var confirmation = MessageBox.Show("Are you sure?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (confirmation == DialogResult.Yes)
                {
                    File.Delete(getTileNodeByName(getSelectedTile()).Attribute("sprite").Value.Substring(5));
                    getTileNodeByName(getSelectedTile()).Remove();
                    configXML.Save("data/config.xml");
                    MessageBox.Show("Tile deleted!", "Deleted.", MessageBoxButtons.OK, MessageBoxIcon.Information);

                    loadTiles();
                    loadTileSets();
                }
            }
        }

        /* Edit Selected Tile */
        private void editTile_Click(object sender, EventArgs e)
        {
            if (getTileNodeByName(getSelectedTile()).Attribute("mandatory").Value != "true")
            {
                TileEditor tileEditor = new TileEditor(getTileNodeByName(getSelectedTile()));
                tileEditor.Show();
                tileEditor.FormClosed += new FormClosedEventHandler(refreshAllLists);
            }
            else
            {
                MessageBox.Show("Can't edit the default tile!", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /* Preview Tile When Selected */
        private void listTile_SelectedIndexChanged(object sender, EventArgs e)
        {
            string new_image = getTileNodeByName(getSelectedTile()).Attribute("sprite").Value;
            if (File.Exists(new_image))
            {
                using (var tempPreviewImg = new Bitmap(new_image))
                {
                    //Fixing file lock issue, cheers: https://stackoverflow.com/a/8701772
                    tilePreview.Image = new Bitmap(tempPreviewImg);
                }
            }
        }
    }
}
