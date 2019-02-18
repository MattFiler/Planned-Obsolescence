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
    public partial class MapList : Form
    {
        public MapList()
        {
            InitializeComponent();
        }

        XDocument configXML;
        private void MapList_Load(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");

            refreshMapList();
        }

        /* Refresh List */
        void refreshMapList()
        {
            configXML = XDocument.Load("data/config.xml");
            clearMaps();
            foreach (XElement element in configXML.Element("config").Element("map_config").Descendants("map"))
            {
                listMapSets.Items.Add(element.Attribute("name").Value);
            }
        }
        void clearMaps()
        {
            listMapSets.Items.Clear();
        }

        /* Refresh On Editor Close */
        private void editorCloseRefresh(object sender, EventArgs e)
        {
            refreshMapList();
        }

        /* Get Map Node By Name */
        XElement getMapNodeByName(string name)
        {
            foreach (XElement element in configXML.Element("config").Element("map_config").Descendants("map"))
            {
                if (element.Attribute("name").Value == name)
                {
                    return element;
                }
            }
            return null;
        }

        /* New Map Set */
        private void newMap_Click(object sender, EventArgs e)
        {
            MapEditor mapEditor = new MapEditor();
            mapEditor.Show();
            mapEditor.FormClosed += new FormClosedEventHandler(editorCloseRefresh);
        }

        /* Delete Selected Map Set */
        private void deleteMap_Click(object sender, EventArgs e)
        {
            if (listMapSets.SelectedIndex != -1)
            {
                XElement toDelete = getMapNodeByName(listMapSets.SelectedItem.ToString());
                if (toDelete.Attribute("mandatory").Value == "true")
                {
                    MessageBox.Show("Cannot delete the default map definition.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    var confirmation = MessageBox.Show("Are you sure?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                    if (confirmation == DialogResult.Yes)
                    {
                        toDelete.Remove();
                        configXML.Save("data/config.xml");
                        MessageBox.Show("Map set deleted!", "Deleted.", MessageBoxButtons.OK, MessageBoxIcon.Information);

                        refreshMapList();
                    }
                }
            }
            else
            {
                MessageBox.Show("Please select a map set to delete.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /* Edit Selected Map */
        private void editMap_Click(object sender, EventArgs e)
        {
            if (listMapSets.SelectedIndex != -1)
            {
                MapEditor mapEditor = new MapEditor(getMapNodeByName(listMapSets.SelectedItem.ToString()));
                mapEditor.Show();
                mapEditor.FormClosed += new FormClosedEventHandler(editorCloseRefresh);
            }
            else
            {
                MessageBox.Show("Please select a map set to edit.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
