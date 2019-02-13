using System;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using Newtonsoft.Json;

namespace PO_Launcher
{
    public partial class PO_Launcher : Form
    {
        JsonTextReader game_config;

        public PO_Launcher()
        {
            InitializeComponent();

            this.FormClosing += PO_Launcher_FormClosing1;
        }

        /* Launcher Load */
        private void PO_Launcher_Load(object sender, EventArgs e)
        {
            //Load image and select default res
            launcherImage.Image = new Bitmap(Properties.Resources.launcher_banner);
            resolutionSelector.SelectedIndex = 0;

            //Get current game config 
            readConfigFromZip();

            //Load keybinds from config
            //game_config.Value;
        }

        /* Launcher Close */
        private void PO_Launcher_FormClosing1(object sender, FormClosingEventArgs e)
        {
            //Replace old config with new one
            writeConfigToZip();
        }

        /* Request Quit Launcher */
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

        /* Read Config */
        void readConfigFromZip()
        {
            using (FileStream zipToOpen = new FileStream("game.dat", FileMode.Open))
            {
                using (ZipArchive archive = new ZipArchive(zipToOpen, ZipArchiveMode.Read))
                {
                    game_config = new JsonTextReader(new StreamReader(archive.GetEntry("CONFIGS/game_core.json").Open()));
                }
            }
        }

        void writeConfigToZip()
        {
            /*
            using (FileStream zipToOpen = new FileStream("game.dat", FileMode.Open))
            {
                using (ZipArchive archive = new ZipArchive(zipToOpen, ZipArchiveMode.Update))
                {
                    archive.entry
                    ZipArchiveEntry readmeEntry = archive.CreateEntry("Readme.txt");
                    using (StreamWriter writer = new StreamWriter(readmeEntry.Open()))
                    {
                        writer.WriteLine("Information about this package.");
                        writer.WriteLine("========================");
                    }
                }
            }
            */
        }
    }
}
