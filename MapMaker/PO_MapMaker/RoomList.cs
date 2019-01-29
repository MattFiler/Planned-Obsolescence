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

        /* Edit Selected Room */
        private void editRoom_Click(object sender, EventArgs e)
        {

        }

        /* Delete Selected Room */
        private void deleteRoom_Click(object sender, EventArgs e)
        {

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
