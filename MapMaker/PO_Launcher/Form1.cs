using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using SharpPhysFS;
using System.IO;

namespace PO_Launcher
{
    public partial class PO_Launcher : Form
    {
        public PO_Launcher()
        {
            InitializeComponent();
        }

        /* Launcher Load */
        private void PO_Launcher_Load(object sender, EventArgs e)
        {
            //Load image and select default res
            launcherImage.Image = new Bitmap(Properties.Resources.launcher_banner);
            resolutionSelector.SelectedIndex = 0;

            //Load keybinds
            /*
            using (var pfs = new PhysFS("game.dat")) 
            using (var reader = new StreamReader(pfs.OpenRead("/data/CONFIGS/game_core.json")))
            {
                var contents = reader.ReadToEnd();
                File.WriteAllText("test.json", contents);
            }
            */
        }

        /* Quit Launcher */
        private void quitButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /* Launch Game */
        private void playButton_Click(object sender, EventArgs e)
        {
            Process.Start("PlannedObsolescence.exe");
            this.Close();
        }
    }
}
