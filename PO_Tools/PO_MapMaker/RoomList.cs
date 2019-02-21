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
    public partial class RoomList : Form
    {
        public RoomList()
        {
            InitializeComponent();
        }

        XDocument configXML;
        private void RoomList_Load(object sender, EventArgs e)
        {
            configXML = XDocument.Load("data/config.xml");

            refreshMapList();
        }

        /* Refresh List */
        void refreshMapList()
        {
            configXML = XDocument.Load("data/config.xml");
            clearMaps();
            foreach (XElement element in configXML.Element("config").Element("room_config").Element("rooms").Descendants("room"))
            {
                listRooms.Items.Add(element.Attribute("name").Value);
            }
        }
        void clearMaps()
        {
            listRooms.Items.Clear();
        }

        /* Refresh On Editor Close */
        private void editorCloseRefresh(object sender, EventArgs e)
        {
            refreshMapList();
        }

        /* Get Room Node By Name */
        XElement getRoomNodeByName(string name)
        {
            foreach (XElement element in configXML.Element("config").Element("room_config").Element("rooms").Descendants("room"))
            {
                if (element.Attribute("name").Value == name)
                {
                    return element;
                }
            }
            return null;
        }

        /* Edit Selected Room */
        private void editRoom_Click(object sender, EventArgs e)
        {
            if (listRooms.SelectedIndex != -1)
            {
                RoomEditor roomEditor = new RoomEditor(getRoomNodeByName(listRooms.Items[listRooms.SelectedIndex].ToString()));
                roomEditor.Show();
                roomEditor.FormClosed += new FormClosedEventHandler(editorCloseRefresh);
            }
            else
            {
                MessageBox.Show("Please select a room to edit.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /* Delete Selected Room */
        private void deleteRoom_Click(object sender, EventArgs e)
        {
            if (listRooms.SelectedIndex != -1)
            {
                XElement toDelete = getRoomNodeByName(listRooms.Items[listRooms.SelectedIndex].ToString());
                if (toDelete.Attribute("mandatory").Value == "true")
                {
                    MessageBox.Show("Cannot delete the default room definition.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    var confirmation = MessageBox.Show("Are you sure?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                    if (confirmation == DialogResult.Yes)
                    {
                        toDelete.Remove();
                        configXML.Save("data/config.xml");
                        MessageBox.Show("Room deleted!", "Deleted.", MessageBoxButtons.OK, MessageBoxIcon.Information);

                        refreshMapList();
                    }
                }
            }
            else
            {
                MessageBox.Show("Please select a room to delete.", "Error.", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /* New Room */
        private void newRoom_Click(object sender, EventArgs e)
        {
            RoomEditor roomEditor = new RoomEditor();
            roomEditor.Show();
            roomEditor.FormClosed += new FormClosedEventHandler(editorCloseRefresh);
        }
    }
}
