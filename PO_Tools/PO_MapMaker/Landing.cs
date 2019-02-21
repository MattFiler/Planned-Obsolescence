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

        /* Create XML On Load If Non-Existant */
        private void Landing_Load(object sender, EventArgs e)
        {
            //Create required directories (unless they already exist) 
            Directory.CreateDirectory("data/CHARACTERS/BOSS");
            Directory.CreateDirectory("data/CHARACTERS/DEFAULT");
            Directory.CreateDirectory("data/CHARACTERS/GOON");
            Directory.CreateDirectory("data/CHARACTERS/GUARD");
            Directory.CreateDirectory("data/CHARACTERS/TECH");
            Directory.CreateDirectory("data/CONFIGS");
            Directory.CreateDirectory("data/TILES");
            Directory.CreateDirectory("data/ROOMS");
            Directory.CreateDirectory("data/MAPS");

            //Output placeholder sprite for tiles
            if (!File.Exists("data/TILES/placeholder.png"))
            { 
                MemoryStream stream = new MemoryStream();
                Properties.Resources.placeholder_tile.Save(stream, System.Drawing.Imaging.ImageFormat.Png);
                File.WriteAllBytes("data/TILES/placeholder.png", stream.ToArray());
            }

            //Output placeholder sprite for characters
            if (!File.Exists("data/CHARACTERS/DEFAULT/placeholder.png"))
            {
                MemoryStream stream2 = new MemoryStream();
                Properties.Resources.placeholder_character.Save(stream2, System.Drawing.Imaging.ImageFormat.Png);
                File.WriteAllBytes("data/CHARACTERS/DEFAULT/placeholder.png", stream2.ToArray());
            }

            //Output placeholder sprite for rooms
            if (!File.Exists("data/ROOMS/default.png"))
            {
                MemoryStream stream = new MemoryStream();
                Properties.Resources.placeholder_room_trans.Save(stream, System.Drawing.Imaging.ImageFormat.Png);
                File.WriteAllBytes("data/ROOMS/default.png", stream.ToArray());
            }

            //Output placeholder sprite for maps
            if (!File.Exists("data/MAPS/default.png"))
            {
                MemoryStream stream = new MemoryStream();
                Properties.Resources.placeholder_map_trans.Save(stream, System.Drawing.Imaging.ImageFormat.Png);
                File.WriteAllBytes("data/MAPS/default.png", stream.ToArray());
            }

            //Create skeleton config file
            if (!File.Exists("data/config.xml"))
            {
                XElement configBasics = new XElement("config",
                    new XElement("tile_config",
                        new XElement("sets", 
                            new XElement("set", new XAttribute("name", "DEFAULT"))
                        ),
                        new XElement("tiles",
                            new XElement("tile", new XAttribute("name", "DEFAULT"), new XAttribute("set", "DEFAULT"), new XAttribute("sprite", "data/TILES/placeholder.png"), new XAttribute("mandatory", "true"),
                                new XElement("dimensions", new XAttribute("width", "50"), new XAttribute("height", "50")),
                                new XElement("valid_exits", new XAttribute("left", "false"), new XAttribute("right", "false"), new XAttribute("up", "false"), new XAttribute("down", "false")),
                                new XElement("points_of_interest", new XAttribute("computer", "false"), new XAttribute("door", "false"), new XAttribute("description", ""), new XAttribute("alt_sprite", ""))
                            )
                        )
                    ),
                    new XElement("room_config",
                        new XElement("rooms",
                            new XElement("room", new XAttribute("name", "DEFAULT"), new XAttribute("mandatory", "true"),
                                new XElement("tiles", new XAttribute("width", "5"), new XAttribute("height", "5"),
                                    new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")),
                                    new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")),
                                    new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")),
                                    new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")),
                                    new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT")), new XElement("tile", new XAttribute("name", "DEFAULT"))
                                )
                            )
                        )
                    ),
                    new XElement("map_config",
                        new XElement("map", new XAttribute("name", "DEFAULT"), new XAttribute("width", "5"), new XAttribute("height", "3"), new XAttribute("mandatory", "true"),
                            new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")),
                            new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")),
                            new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT")), new XElement("room", new XAttribute("name", "DEFAULT"))
                        )
                    ),
                    new XElement("character_config", 
                        new XElement("character", new XAttribute("type", "DEFAULT"),
                            new XElement("misc", 
                                new XAttribute("movement_speed", "5"), 
                                new XAttribute("max_health", "100"), 
                                new XAttribute("spawn_cap", "10"), 
                                new XAttribute("is_visible", "true")
                            ),
                            new XElement("sprites",
                                new XAttribute("default", "data/CHARACTERS/DEFAULT/placeholder.png")
                            ),
                            new XElement("gauges",
                                new XAttribute("suspicion", "0"),
                                new XAttribute("stress", "0"),
                                new XAttribute("productivity", "100"),
                                new XAttribute("faith", "100")
                            ),
                            new XElement("spawn_pos",
                                new XAttribute("x", "0"),
                                new XAttribute("y", "0")
                            ),
                            new XElement("dimensions",
                                new XAttribute("width", "50"),
                                new XAttribute("height", "50")
                            )
                        ),
                        new XElement("character", new XAttribute("type", "GUARD")),
                        new XElement("character", new XAttribute("type", "GOON")),
                        new XElement("character", new XAttribute("type", "BOSS")),
                        new XElement("character", new XAttribute("type", "TECH"))
                    ),
                    new XElement("game_config", 
                        new XElement("resolution", 
                            new XAttribute("width", "1920"), 
                            new XAttribute("height", "1080")
                        ),
                        new XElement("debug", 
                            new XAttribute("enabled", "false")
                        ),
                        new XElement("keybinds",
                            new XElement("bind", new XAttribute("key", "KEY_ENTER"), new XAttribute("action", "Activate")),
                            new XElement("bind", new XAttribute("key", "KEY_ESCAPE"), new XAttribute("action", "Back"))
                        )
                    )
                );
                configBasics.Save("data/config.xml");
            }
        }

        /* Open Tile List */
        private void openTileEditor_Click(object sender, EventArgs e)
        {
            TileList tileList = new TileList();
            tileList.Show();
        }

        /* Open Game Editor */
        private void openGameEditor_Click(object sender, EventArgs e)
        {
            GameEditor gameEditor = new GameEditor();
            gameEditor.Show();
        }

        /* Open Character Editor */
        private void openCharacterEditor_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Coming soon.", "", MessageBoxButtons.OK, MessageBoxIcon.Stop);
        }

        /* Compile Config */
        private void startCompile_Click(object sender, EventArgs e)
        {
            Compiler compilerProcess = new Compiler();
            compilerProcess.Show();
        }

        /* Open Room Editor */
        private void openRoomEditor_Click(object sender, EventArgs e)
        {
            RoomList roomEditor = new RoomList();
            roomEditor.Show();
        }

        /* Open Keybind Editor */
        private void openKeybindEditor_Click(object sender, EventArgs e)
        {
            KeybindEditor keyEditor = new KeybindEditor();
            keyEditor.Show();
        }
        
        /* Open Map Editor */
        private void openMapEditor_Click(object sender, EventArgs e)
        {
            MapList mapEditor = new MapList();
            mapEditor.Show();
        }
    }
}
