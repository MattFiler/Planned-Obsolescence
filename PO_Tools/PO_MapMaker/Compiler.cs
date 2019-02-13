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

            /* map_core.json */
            statusText.Text = "Compiling Map Data";
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
                    rooms_coreJson = rooms_coreJson.Substring(0, rooms_coreJson.Length - 1) + "]},";
                }
                else
                {
                    rooms_coreJson += "\"" + room.Attribute("name").Value + "\":{ ";
                    rooms_coreJson += addElementIfNotDefault("width", default_room.Element("tiles").Attribute("width"), room.Element("tiles").Attribute("width"), false);
                    rooms_coreJson += addElementIfNotDefault("height", default_room.Element("tiles").Attribute("height"), room.Element("tiles").Attribute("height"), false);
                    rooms_coreJson += "\"tiles\":[ ";
                    foreach (XElement tile in room.Element("tiles").Descendants("tile"))
                    {
                        rooms_coreJson += "\"" + tile.Attribute("name").Value + "\",";
                    }
                    rooms_coreJson = rooms_coreJson.Substring(0, rooms_coreJson.Length - 1) + "]},";
                }
            }
            rooms_coreJson = rooms_coreJson.Substring(0, rooms_coreJson.Length - 1) + "}";
            JToken rooms_coreJsonParsed = JToken.Parse(rooms_coreJson);
            File.WriteAllText("data/CONFIGS/rooms_core.json", rooms_coreJsonParsed.ToString(Formatting.Indented));
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
                    tiles_coreJson += "\"DEFAULT\":{\"width\":"+ tile.Element("dimensions").Attribute("width").Value+",\"height\":"+tile.Element("dimensions").Attribute("height").Value+",\"sprite\":\""+ tile.Attribute("sprite").Value+"\",\"available_exits\":{\"left\":"+tile.Element("valid_exits").Attribute("left").Value+",\"right\":" + tile.Element("valid_exits").Attribute("right").Value + ",\"up\":" + tile.Element("valid_exits").Attribute("up").Value + ",\"down\":" + tile.Element("valid_exits").Attribute("down").Value + "},\"has_point_of_interest\":{\"door\":"+ tile.Element("points_of_interest").Attribute("door").Value+",\"computer\":"+ tile.Element("points_of_interest").Attribute("computer").Value+"}},";
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
                        tiles_coreJson += "\"has_point_of_interest\":{" + points_of_interest.Substring(0,points_of_interest.Length-1) + "},";
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

        /* Reference: https://docs.microsoft.com/en-us/dotnet/standard/io/how-to-copy-directories */
        private static void directoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
        {
            // Get the subdirectories for the specified directory.
            DirectoryInfo dir = new DirectoryInfo(sourceDirName);

            if (!dir.Exists)
            {
                throw new DirectoryNotFoundException(
                    "Source directory does not exist or could not be found: "
                    + sourceDirName);
            }

            DirectoryInfo[] dirs = dir.GetDirectories();
            // If the destination directory doesn't exist, create it.
            if (!Directory.Exists(destDirName))
            {
                Directory.CreateDirectory(destDirName);
            }

            // Get the files in the directory and copy them to the new location.
            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string temppath = Path.Combine(destDirName, file.Name);
                file.CopyTo(temppath, false);
            }

            // If copying subdirectories, copy them and their contents to new location.
            if (copySubDirs)
            {
                foreach (DirectoryInfo subdir in dirs)
                {
                    string temppath = Path.Combine(destDirName, subdir.Name);
                    directoryCopy(subdir.FullName, temppath, copySubDirs);
                }
            }
        }
    }
}
