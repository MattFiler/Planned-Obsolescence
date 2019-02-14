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
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO.Compression;

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
            XDocument configXML = XDocument.Load("data/config.xml");

            /* characters_core.json */
            statusText.Text = "Compiling Character Data";
            //WIP
            progressBar.PerformStep();

            /* map_core.json */
            statusText.Text = "Compiling Map Data";
            //WIP
            progressBar.PerformStep();

            /* game_core.json */
            statusText.Text = "Compiling Game Configurations";
            XElement game_config = configXML.Element("config").Element("game_config");
            string game_coreJson = "{\"DEFAULT\":{\"resolution\":{\"width\": " + game_config.Element("resolution").Attribute("width").Value + ",\"height\": " + game_config.Element("resolution").Attribute("height").Value + "},\"debug_enabled\": " + game_config.Element("debug").Attribute("enabled").Value + ",\"keybinds\":{";
            foreach (XElement binds in game_config.Element("keybinds").Descendants("bind"))
            {
                game_coreJson += "\"" + binds.Attribute("action").Value + "\": " + keynameToKeycode(binds.Attribute("key").Value) + ",";
            }
            game_coreJson = game_coreJson.Substring(0, game_coreJson.Length - 1) + "}}}";
            JToken game_coreJsonParsed = JToken.Parse(game_coreJson);
            File.WriteAllText("data/CONFIGS/game_core.json", game_coreJsonParsed.ToString(Formatting.Indented));
            progressBar.PerformStep();

            /* tiles_core.json */
            statusText.Text = "Compiling Tile Data";
            XElement tile_config = configXML.Element("config").Element("tile_config").Element("tiles");
            XElement default_tile = null;
            foreach (XElement tile in tile_config.Elements())
            {
                if (tile.Attribute("set").Value == "DEFAULT")
                {
                    //Get default tile
                    default_tile = tile;
                    break;
                }
            }
            string tiles_coreJson = "{";
            foreach (XElement tile in tile_config.Elements())
            {
                if (tile.Attribute("set").Value == "DEFAULT")
                {
                    //Default is an ugly mess. Apologies...
                    tiles_coreJson += "\"DEFAULT\":{\"width\":" + tile.Element("dimensions").Attribute("width").Value + ",\"height\":" + tile.Element("dimensions").Attribute("height").Value + ",\"sprite\":\"" + tile.Attribute("sprite").Value + "\",\"available_exits\":{\"left\":" + tile.Element("valid_exits").Attribute("left").Value + ",\"right\":" + tile.Element("valid_exits").Attribute("right").Value + ",\"up\":" + tile.Element("valid_exits").Attribute("up").Value + ",\"down\":" + tile.Element("valid_exits").Attribute("down").Value + "},\"has_point_of_interest\":{\"door\":" + tile.Element("points_of_interest").Attribute("door").Value + ",\"computer\":" + tile.Element("points_of_interest").Attribute("computer").Value + "}},";
                    //...aaaand it's over. Back to neater code.
                }
                else
                {
                    tiles_coreJson += "\"" + tile.Attribute("name").Value + "\":{ ";
                    tiles_coreJson += addElementIfNotDefault("width", default_tile.Element("dimensions").Attribute("width"), tile.Element("dimensions").Attribute("width"), false);
                    tiles_coreJson += addElementIfNotDefault("height", default_tile.Element("dimensions").Attribute("height"), tile.Element("dimensions").Attribute("height"), false);
                    tiles_coreJson += addElementIfNotDefault("sprite", default_tile.Attribute("sprite"), tile.Attribute("sprite"));

                    string available_exits = "";
                    string[] directions = { "left", "right", "up", "down" };
                    foreach (string direction in directions)
                    {
                        available_exits += addElementIfNotDefault(direction, default_tile.Element("valid_exits").Attribute(direction), tile.Element("valid_exits").Attribute(direction), false);
                    }
                    if (available_exits != "")
                    {
                        tiles_coreJson += "\"available_exits\":{" + available_exits.Substring(0, available_exits.Length - 1) + "},";
                    }

                    string points_of_interest = "";
                    string[] pois = { "door", "computer" };
                    foreach (string poi in pois)
                    {
                        points_of_interest += addElementIfNotDefault(poi, default_tile.Element("points_of_interest").Attribute(poi), tile.Element("points_of_interest").Attribute(poi), false);
                    }
                    if (points_of_interest != "")
                    {
                        tiles_coreJson += "\"has_point_of_interest\":{" + points_of_interest.Substring(0, points_of_interest.Length - 1) + "},";
                    }

                    tiles_coreJson = tiles_coreJson.Substring(0, tiles_coreJson.Length - 1) + "},";
                }
            }
            tiles_coreJson = tiles_coreJson.Substring(0, tiles_coreJson.Length - 1) + "}";

            //I'm giving in and using a library for a little of this process.
            //Minified files don't work nice with git!
            JToken tiles_coreJsonParsed = JToken.Parse(tiles_coreJson);
            File.WriteAllText("data/CONFIGS/tiles_core.json", tiles_coreJsonParsed.ToString(Formatting.Indented));
            progressBar.PerformStep();

            /* rooms_core.json */
            statusText.Text = "Compiling Room Data";
            XElement room_config = configXML.Element("config").Element("room_config").Element("rooms");
            XElement default_room = null;
            foreach (XElement room in room_config.Descendants("room"))
            {
                if (room.Attribute("name").Value == "DEFAULT")
                {
                    //Get default room
                    default_room = room;
                    break;
                }
            }
            DirectoryInfo existing_room_sprites = new DirectoryInfo("data/ROOMS");
            foreach (var file in existing_room_sprites.GetFiles("*.png"))
            {
                if (file.Name != "default.png")
                {
                    File.Delete(file.FullName);
                }
            }
            string rooms_coreJson = "{";
            foreach (XElement room in room_config.Descendants("room"))
            {
                if (room.Attribute("name").Value == "DEFAULT")
                {
                    rooms_coreJson += "\"DEFAULT\":{\"tile_w\":" + room.Element("tiles").Attribute("width").Value + ",\"tile_h\":" + room.Element("tiles").Attribute("height").Value + ",\"tiles\":[ ";
                    foreach (XElement tile in room.Element("tiles").Descendants("tile"))
                    {
                        rooms_coreJson += "\"" + tile.Attribute("name").Value + "\",";
                    }
                    rooms_coreJson = rooms_coreJson.Substring(0, rooms_coreJson.Length - 1) + "],\"sprite\":\"data/ROOMS/default.png\"},";
                }
                else
                {
                    int room_width = Convert.ToInt32(room.Element("tiles").Attribute("width").Value);
                    int room_height = Convert.ToInt32(room.Element("tiles").Attribute("height").Value);
                    List<Bitmap> room_tiles = new List<Bitmap>(); 
                    List<int[]> room_tile_dimensions = new List<int[]>();
                    List<int[]> room_tile_position = new List<int[]>();

                    rooms_coreJson += "\"" + room.Attribute("name").Value + "\":{ ";
                    rooms_coreJson += addElementIfNotDefault("width", default_room.Element("tiles").Attribute("width"), room.Element("tiles").Attribute("width"), false);
                    rooms_coreJson += addElementIfNotDefault("height", default_room.Element("tiles").Attribute("height"), room.Element("tiles").Attribute("height"), false);
                    rooms_coreJson += "\"tiles\":[ ";

                    int tile_index = 0;
                    int[] tile_pos = { 0, 0 };
                    foreach (XElement tile in room.Element("tiles").Descendants("tile"))
                    {
                        //Save this tile's data for creating the room sprite
                        foreach (XElement tile_data in tile_config.Elements())
                        {
                            if (tile_data.Attribute("name").Value == tile.Attribute("name").Value)
                            {
                                //Get tile sprite
                                room_tiles.Add(loadBMP(tile_data.Attribute("sprite").Value));

                                //Get tile dimensions
                                int[] tile_dims = {
                                    Convert.ToInt32(parseForDefaultPlaceholder(tile_data.Element("dimensions").Attribute("width").Value, default_tile.Element("dimensions").Attribute("width").Value)),
                                    Convert.ToInt32(parseForDefaultPlaceholder(tile_data.Element("dimensions").Attribute("height").Value, default_tile.Element("dimensions").Attribute("height").Value))
                                };
                                room_tile_dimensions.Add(tile_dims);

                                //Calculate tile position
                                if ((tile_index) % room_width == 0)
                                {
                                    if (tile_index >= room_width)
                                    {
                                        tile_pos[0] = 0;
                                        tile_pos[1] += tile_dims[1];
                                    }
                                }
                                else
                                {
                                    tile_pos[0] += tile_dims[0];
                                }
                                int[] this_tile_pos = { tile_pos[0], tile_pos[1] };
                                room_tile_position.Add(this_tile_pos);
                                break;
                            }
                        }
                        tile_index++;

                        //Add tile to json list
                        rooms_coreJson += "\"" + tile.Attribute("name").Value + "\",";
                    }

                    //Room size
                    int room_width_actual = room_tile_position[room_tiles.Count - 1][0] + room_tile_dimensions[room_tiles.Count - 1][0];
                    int room_height_actual = room_tile_position[room_tiles.Count - 1][1] + room_tile_dimensions[room_tiles.Count - 1][1];
                    
                    //Load placeholder bitmap to draw over
                    Bitmap room_sprite = loadBMP("data/ROOMS/default.png", room_width_actual, room_height_actual);
                    Graphics room_graphics = Graphics.FromImage(room_sprite);

                    //Draw over bitmap with our room tiles
                    int bitmap_index = 0;
                    foreach (Bitmap tile_sprite in room_tiles)
                    {
                        int[] tile_dimensions = room_tile_dimensions[bitmap_index];
                        int[] tile_position = room_tile_position[bitmap_index];

                        room_graphics.DrawImage(tile_sprite, tile_position[0], tile_position[1], tile_dimensions[0], tile_dimensions[1]);

                        bitmap_index++;
                    }
                    room_graphics.Dispose();

                    //Save room sprite
                    string room_sprite_filepath = "data/ROOMS/" + room.Attribute("name").Value + "_" + DateTime.Now.ToString("hhmmss") + ".png";
                    room_sprite.Save(room_sprite_filepath);

                    //Finish JSON
                    rooms_coreJson = rooms_coreJson.Substring(0, rooms_coreJson.Length - 1) + "],\"sprite\":\"" + room_sprite_filepath + "\"},";
                }
            }
            rooms_coreJson = rooms_coreJson.Substring(0, rooms_coreJson.Length - 1) + "}";
            JToken rooms_coreJsonParsed = JToken.Parse(rooms_coreJson);
            File.WriteAllText("data/CONFIGS/rooms_core.json", rooms_coreJsonParsed.ToString(Formatting.Indented));
            progressBar.PerformStep();

            /* Copy Everything */
            statusText.Text = "Finishing up...";
            if (File.Exists("cmake-build-debug/bin/game.dat"))
            {
                File.Delete("cmake-build-debug/bin/game.dat");
                ZipFile.CreateFromDirectory("data", "cmake-build-debug/bin/game.dat");
                MessageBox.Show("Finished compiling!\nRelaunch the game to try out the changes.", "Completed.", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Finished!\nCompile the game in CLion to try out the changes.", "Completed.", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            progressBar.PerformStep();

            /* Exit */
            UseWaitCursor = false;
            this.Close();
        }

        /* JSON-ify some data (who needs libraries?) */
        string addElementIfNotDefault(string param_name, XAttribute default_value, XAttribute this_value, bool include_speechmarks = true, bool include_comma = true)
        {
            string to_return = "";
            if (default_value.Value != this_value.Value && this_value.Value != "DEFAULT")
            {
                to_return += "\"" + param_name + "\":";
                if (include_speechmarks) { to_return += "\""; }
                to_return += this_value.Value;
                if (include_speechmarks) { to_return += "\""; }
                if (include_comma) { to_return += ","; }
            }
            return to_return;
        }

        /* A simple fix to replace "DEFAULT" with the default value */
        string parseForDefaultPlaceholder(string input, string default_value)
        {
            if (input != "DEFAULT")
            {
                return input;
            }
            else
            {
                return default_value;
            }
        }

        /* Convert Key Name to Code */
        int keynameToKeycode(string keyname)
        {
            switch (keyname)
            {
                case "KEY_SPACE": return 32;
                case "KEY_APOSTROPHE": return 39;
                case "KEY_COMMA": return 44;
                case "KEY_MINUS": return 45;
                case "KEY_PERIOD": return 46;
                case "KEY_SLASH": return 47;
                case "KEY_0": return 48;
                case "KEY_1": return 49;
                case "KEY_2": return 50;
                case "KEY_3": return 51;
                case "KEY_4": return 52;
                case "KEY_5": return 53;
                case "KEY_6": return 54;
                case "KEY_7": return 55;
                case "KEY_8": return 56;
                case "KEY_9": return 57;
                case "KEY_SEMICOLON": return 59;
                case "KEY_EQUAL": return 61;
                case "KEY_A": return 65;
                case "KEY_B": return 66;
                case "KEY_C": return 67;
                case "KEY_D": return 68;
                case "KEY_E": return 69;
                case "KEY_F": return 70;
                case "KEY_G": return 71;
                case "KEY_H": return 72;
                case "KEY_I": return 73;
                case "KEY_J": return 74;
                case "KEY_K": return 75;
                case "KEY_L": return 76;
                case "KEY_M": return 77;
                case "KEY_N": return 78;
                case "KEY_O": return 79;
                case "KEY_P": return 80;
                case "KEY_Q": return 81;
                case "KEY_R": return 82;
                case "KEY_S": return 83;
                case "KEY_T": return 84;
                case "KEY_U": return 85;
                case "KEY_V": return 86;
                case "KEY_W": return 87;
                case "KEY_X": return 88;
                case "KEY_Y": return 89;
                case "KEY_Z": return 90;
                case "KEY_LEFT_BRACKET": return 91;
                case "KEY_BACKSLASH": return 92;
                case "KEY_RIGHT_BRACKET": return 93;
                case "KEY_GRAVE_ACCENT": return 96;
                case "KEY_WORLD_1": return 161;
                case "KEY_WORLD_2": return 162;
                case "KEY_ESCAPE": return 256;
                case "KEY_ENTER": return 257;
                case "KEY_TAB": return 258;
                case "KEY_BACKSPACE": return 259;
                case "KEY_DELETE": return 261;
                case "KEY_RIGHT": return 262;
                case "KEY_LEFT": return 263;
                case "KEY_DOWN": return 264;
                case "KEY_UP": return 265;
                default: return 0;
            }
        }

        /* Load a bitmap safely */
        Bitmap loadBMP(string filepath, int x = 0, int y = 0)
        {
            if (x == 0 && y == 0)
            {
                using (var tempPreviewImg = new Bitmap(filepath))
                {
                    return new Bitmap(tempPreviewImg);
                }
            }
            else
            {
                using (var tempPreviewImg = new Bitmap(filepath))
                {
                    return new Bitmap(tempPreviewImg, x, y);
                }
            }
        }
    }
}
