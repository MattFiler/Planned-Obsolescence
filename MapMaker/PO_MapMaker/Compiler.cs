using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PO_MapMaker
{
    public partial class Compiler : Form
    {
        public Compiler()
        {
            InitializeComponent();
        }

        private void Compiler_Load(object sender, EventArgs e)
        {
            UseWaitCursor = true;

            /* characters_core.json */
            statusText.Text = "Compiling Character Data";
            progressBar.PerformStep();

            /* game_core.json */
            statusText.Text = "Compiling Game Configurations";
            progressBar.PerformStep();

            /* map_core.json */
            statusText.Text = "Compiling Map Data";
            progressBar.PerformStep();

            /* rooms_core.json */
            statusText.Text = "Compiling Room Data";
            progressBar.PerformStep();
            
            /* tiles_core.json */
            statusText.Text = "Compiling Tile Data";
            progressBar.PerformStep();

            /* Copy Everything */
            statusText.Text = "Finishing up...";
            progressBar.PerformStep();

            UseWaitCursor = false;
            this.Close();
        }
    }
}
