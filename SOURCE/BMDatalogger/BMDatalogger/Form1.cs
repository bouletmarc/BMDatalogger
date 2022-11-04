using System;
using System.IO;
using System.Globalization;
using System.Diagnostics;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Net;
using System.Windows.Forms;

namespace BMDatalogger
{
    public partial class Form1 : Form
    {
        private System.Windows.Forms.Timer LoadTimer = new System.Windows.Forms.Timer();

        public string Github_Get_Url = "https://raw.githubusercontent.com/bouletmarc/BMDatalogger/master/";
        public string Github_Download_Url = "https://github.com/bouletmarc/BMDatalogger/raw/master/";
        public List<string> Filelist = new List<string>();

        string Version = "V2.0.1";
        string BMDataloggerVersion = "";
        string SettingsVersion = "";

        int Timeout = 60;
        int InjSize = 240;
        byte O2Input = 0;
        byte MapValue = 0;
        byte UseCelcius = 1;
        byte UseKMH = 1;
        byte O2Type = 0;
        byte ProgressBarMode = 0;
        byte ProgressBarLeft = 0;
        byte ScreenCurrentPage = 1;
        byte ScreenCurrentMenu = 0;
        bool IsLoadingPage = false;
        int[] ScreenPage1 = new int[] { 100, 0, 1, 2, 3, 4, 5, 6 };
        int[] ScreenPage2 = new int[] { 100, 0, 7, 8, 9, 10, 11, 12 };
        int[] ScreenPage3 = new int[] { 100, 0, 13, 14, 15, 16, 17, 18 };
        int[] ScreenPage4 = new int[] { 100, 0, 101, 10, 102, 0, 103, 0 };
        int[] ScreenPage5 = new int[] { 100, 0, 106, 0, 116, 0, 8, 16 };
        int[] ScreenPage6 = new int[] { 100, 0, 5, 9, 2, 4, 118, 0 };
        int[] ScreenPage7 = new int[] { 100, 0, 118, 0, 106, 0, 103, 0 };
        int[] ScreenPage8 = new int[] { 1, 2, 200, 0, 0, 0, 3, 4 };
        int[] CurrentPageArray = new int[8];
        double[] WidebandChart = new double[] {
            0, 1.3,
            1, 0.71
        };

        byte[] TrannyByte = new byte[] {
            0x46,
            0x67,
            0x8E,
            0xB8
        };

        byte[] MapByte = new byte[] {
            0xBA,
            0x7F,
            0xFE,
            0x86
        };

        string[] SensorsValues = new string[]
        {
            "RPM",
            "ECT",
            "IAT",
            "TPS",
            "O2",
            "IGN",
            "INJ",
            "FUEL",
            "IACV",
            "MAP",
            "BST",
            "VSS",
            "FAN",
            "BATT",
            "ICUT",
            "FCUT",
            "INJFV",
            "2MAP",
            "TIME",
            "BTIME",
            "VTS",
            "VTP",
            "ELDV",
            "O2H",
            "AC",
            "ALT",
            "GEAR",

            "BST",
            "FTL",
            "ATLG",
            "FTS",
            "EBC",
            "BSTCT",
            "LEAN",
            "PARK",
            "BKSW",
            "ACC",
            "START",
            "SCC",
            "FCUT2",
            "PSP",
            "FPMP",
            "IAB",
            "PURGE",
            "GPO1",
            "GPO2",
            "GPO3",
            "BSTS2",
            "BSTS3",
            "BSTS4",

            "PSTF",
            "SCCCK",
            "VTSM",
            "ATS1",
            "ATS2",
            "VTSFB",
            "FANC",
            "MIL",
            "OHEAT",
            "IGNT",
            "IFTL",
            "IFTS",
            "IEBC",
            "IEBCH",
            "IGPO1",
            "IGPO2",
            "IGPO3",
            "IBST",

            "BARO",
            "INJD",
            "ECTFC",
            "O2SHT",
            "O2LNG",
            "IATFC",
            "VEFC",
            "IATIC",
            "ECTIC",
            "GEARI",
            "EBCBD",
            "EBCDT"
        };

        string[] SensorsDesc = new string[]
        {
            "RPM - Roll Per Minutes",
            "Engine Coolant Temperature",
            "Intake Air Temperature",
            "Throttle Position",
            "O2 Value",
            "Ignition Value",
            "Injector Value",
            "Comsumption L/100km",
            "Intake Air Control Valve",
            "Manifold Absolute Pressure",
            "Boost Pressure",
            "Speed Value",
            "Fan Control",
            "Battery Voltage",
            "Ignition Cut",
            "Fuel Cut",
            "Injector Fuel Value",
            "2nd Map Table",
            "Timer 0-100",
            "Best 0-100",
            "Vtec Active",
            "Vtec Pressure Switch",
            "Electrical Load Detector Voltage",
            "O2 Heater",
            "Air Conditioner",
            "Alternator Control",
            "Current Gear",

            "BST",
            "Full Throttle Launch",
            "Antilag",
            "Full Throttle Shift",
            "Electronic Boost Control",
            "Boost Cut Output",
            "Lean Protection",
            "Park/Neutral Signal",
            "Brake Switch Signal",
            "Air Conditioning Output",
            "Starter Signal",
            "Service Check Connector",
            "Fuel Cut #2",
            "Power Steering Pressure Switch",
            "Fuel Pump Output",
            "Intake Air Butterflies",
            "Purge Solenoid",
            "GPO Output1",
            "GPO Output2",
            "GPO Output3",
            "BST Stage2",
            "BST Stage3",
            "BST Stage4",
            "Post Fuel",
            "SCC Checker",
            "VTSM",
            "Automatic Tranny Shift1",
            "Automatic Tranny Shift2",
            "VTS Feedback",
            "Fan Control",
            "MIL - malfunction engine light",
            "Overheat Protection",
            "Ignition Table",
            "Full Throttle Launch Input",
            "Full Throttle Shift Input",
            "Electronic Boost Controller Input",
            "Electronic Boost Controller Hi Input",
            "GPO Input1",
            "GPO Input2",
            "GPO Input3",
            "Boost Controller Input",
            "Baro",
            "Injector Duty",
            "ECT Fuel Correction",
            "O2 Short",
            "O2 Long",
            "IAT Fuel Correction",
            "VE Fuel Correction",
            "IAT Ignition Correction",
            "ECT Ignition Correction",
            "Gear Ignition Correction",
            "Electronic Boost Controller Base Duty",
            "Electronic Boost Controller Duty"
        };

        int[] PeaksMin = new int[]
        {
            0,
            -40,//
            -40,//
            0,
            10,
            -6,
            0,
            0,
            -100,
            -70,//
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            2,
            2,
            0,
            0,
            0,
            0,
            0,
            0,
            0,

            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,

            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            -6,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            -6,
            -6,
            -6,
            0,
            0
        };

        int[] PeaksMax = new int[]
        {
            11000,
            140,//
            140,//
            100,
            20,
            60,
            20,
            50,
            100,
            1790,//
            40,
            300,
            1,//12
            18,
            1,//14
            1,//15
            3000,
            1,//16
            18,
            18,
            1,//17
            1,//18
            18,
            1,//20
            1,//21
            1,//22
            5,

            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//
            1,//

            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            60,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            4000,
            100,
            255,
            255,
            255,
            255,
            255,
            60,
            60,
            1,
            100,
            100
        };
        
        public bool LockedPeaks(int i)
        {
            bool Locked = false;
            if (i == 12 | i == 14 | i == 15 | i == 17 | i == 18 | i == 20 | i == 21 | i == 23 | i == 24 | i == 25 | (i >= 27 && i < 59) | (i >= 60 && i < 68) | i == 77) Locked = true;
            return Locked;
        }

        public Form1()
        {
            InitializeComponent();

            this.Size = new Size(368, 510);

            this.groupBoxMain.Location = new Point(6, 62);
            this.groupBoxPages.Location = new Point(6, 62);
            this.groupBoxO2Map.Location = new Point(6, 62);
            this.groupBoxDesc.Location = new Point(6, 62);
            this.groupBoxPeaks.Location = new Point(6, 62);

            comboBox_Editing.SelectedIndex = 0;
            SelectEditing();

            comboBox_TempUnit.SelectedIndex = 0;
            comboBox_MapUnit.SelectedIndex = 0;
            comboBox_O2Unit.SelectedIndex = 0;
            comboBox_SpeedUnit.SelectedIndex = 0;
            comboBox_Tranny.SelectedIndex = 0;
            comboBox_ProgressMode.SelectedIndex = 0;
            comboBox_ProgressSide.SelectedIndex = 0;
            comboBox_Page.SelectedIndex = 0;
            comboBox_StartupMenu.SelectedIndex = 0;
            comboBox_O2Input.SelectedIndex = 0;
            comboBox_O2.SelectedIndex = 0;
            comboBox_Map.SelectedIndex = 0;

            //SpawnMapByte();

            LoadTimer.Interval = 100;
            LoadTimer.Tick += LoadingThread;
            LoadTimer.Start();
        }

        /*void SpawnMapByte()
        {
            for (int i = 0; i < 9; i++)
            {
                int At0 = -70;
                int At5 = 1790;
                if (i == 0) { At0 = -70; At5 = 1790; };
                if (i == 1) { At0 = 8; At5 = 2041; };
                if (i == 2) { At0 = 11; At5 = 3155; };
                if (i == 3) { At0 = 70; At5 = 2590; };
                if (i == 4) { At0 = -431; At5 = 3844; };
                if (i == 5) { At0 = 11; At5 = 3040; };
                if (i == 6) { At0 = 35; At5 = 4180; };
                if (i == 7) { At0 = -625; At5 = 5625; };
                if (i == 8) { At0 = 35; At5 = 4180; };

                At0 += 32768;
                At5 += 32768;

                string Low = At0.ToString("X4");
                string High = At5.ToString("X4");

                string Low1 = Low.Substring(0, 2);
                string Low2 = Low.Substring(2);
                string High1 = High.Substring(0, 2);
                string High2 = High.Substring(2);

                string Enfdstr = "{";
                Enfdstr += "0x" + byte.Parse(Low2, NumberStyles.HexNumber, CultureInfo.InvariantCulture).ToString("x2");
                Enfdstr += ", ";
                Enfdstr += "0x" + byte.Parse(Low1, NumberStyles.HexNumber, CultureInfo.InvariantCulture).ToString("x2");
                Enfdstr += ", ";
                Enfdstr += "0x" + byte.Parse(High2, NumberStyles.HexNumber, CultureInfo.InvariantCulture).ToString("x2");
                Enfdstr += ", ";
                Enfdstr += "0x" + byte.Parse(High1, NumberStyles.HexNumber, CultureInfo.InvariantCulture).ToString("x2");
                Enfdstr += "}";

                Console.WriteLine(Enfdstr);
            }
        }*/

        void LoadingThread(object sender, EventArgs e) {
            LoadTimer.Stop();

            CheckConnectionToGithub();

            this.Text = "BMDatalogger Interface " + Version;

            //Load values from settings before Initialize
            LoadSettings();
            if (SettingsVersion != Version) SaveSettings();

            CheckArduinoUpdate();

            Log_This("Initializing Tool...");

            //Reload Old Gear Value (now fan value)
            if (SensorsValues[12] == "GEAR") SensorsValues[12] = "FAN";
            if (SensorsValues[18] == "0-100") SensorsValues[18] = "TIME";
            if (SensorsValues[19] == "B0100") SensorsValues[19] = "BTIME";

            //Initialize Values
            textBox_Timeout.Text = Timeout.ToString();
            textBox_Injector.Text = InjSize.ToString();
            comboBox_O2Input.Text = GetO2Str();
            comboBox_MapUnit.Text = GetMapStr();
            comboBox_TempUnit.Text = GetTempCelcius();
            comboBox_SpeedUnit.Text = GetKMH();
            comboBox_O2Unit.Text = GetLAMBA();
            comboBox_StartupMenu.Text = GetMenu();
            comboBox_Page.Text = ScreenCurrentPage.ToString();
            comboBox_ProgressMode.Text = ProgressBarMode.ToString();
            comboBox_ProgressSide.Text = GetProgressSide();

            //Initialize Pages
            for (int i = 0; i < SensorsValues.Length; i++)
            {
                comboBox_Page1.Items.Add(i + "-" + SensorsValues[i]);
                //comboBox_Page1.Items.Add((i + 100) + "-" + SensorsValues[i] + "-PROGRESS BAR");
                //comboBox_Page1.Items.Add((i + 200) + "-" + SensorsValues[i] + "-SEMI BIG FONT");
                //comboBox_Page1.Items.Add((i + 300) + "-" + SensorsValues[i] + "-BIG FONT");
                comboBox_Page2.Items.Add(i + "-" + SensorsValues[i]);

                comboBox_Page3.Items.Add(i + "-" + SensorsValues[i]);
                //comboBox_Page3.Items.Add((i + 100) + "-" + SensorsValues[i] + "-PROGRESS BAR");
                //comboBox_Page3.Items.Add((i + 200) + "-" + SensorsValues[i] + "-SEMI BIG FONT");
                //comboBox_Page3.Items.Add((i + 300) + "-" + SensorsValues[i] + "-BIG FONT");
                comboBox_Page4.Items.Add(i + "-" + SensorsValues[i]);

                comboBox_Page5.Items.Add(i + "-" + SensorsValues[i]);
                //comboBox_Page5.Items.Add((i + 100) + "-" + SensorsValues[i] + "-PROGRESS BAR");
                //comboBox_Page5.Items.Add((i + 200) + "-" + SensorsValues[i] + "-SEMI BIG FONT");
                //comboBox_Page5.Items.Add((i + 300) + "-" + SensorsValues[i] + "-BIG FONT");
                comboBox_Page6.Items.Add(i + "-" + SensorsValues[i]);

                comboBox_Page7.Items.Add(i + "-" + SensorsValues[i]);
                //comboBox_Page7.Items.Add((i + 100) + "-" + SensorsValues[i] + "-PROGRESS BAR");
                //comboBox_Page7.Items.Add((i + 200) + "-" + SensorsValues[i] + "-SEMI BIG FONT");
                //comboBox_Page7.Items.Add((i + 300) + "-" + SensorsValues[i] + "-BIG FONT");
                comboBox_Page8.Items.Add(i + "-" + SensorsValues[i]);
            }

            //Initialize WB Chart
            for (int i = 0; i < 2; i++)
            {
                string[] RowsVal = new string[3];
                RowsVal[0] = WidebandChart[i * 2].ToString();
                RowsVal[1] = WidebandChart[(i * 2) + 1].ToString();
                RowsVal[2] = (Math.Round((WidebandChart[(i * 2) + 1] * 14.7) * 100) / 100).ToString();
                dataGridView_O2.Rows.Add(RowsVal);
            }

            //Initialize Tranny Chart
            for (int i = 0; i < 4; i++)
            {
                string[] RowsVal = new string[2];
                RowsVal[0] = (i + 1).ToString();
                RowsVal[1] = TrannyByte[i].ToString();
                dataGridView_Tranny.Rows.Add(RowsVal);
            }

            //Initialize Map Chart
            for (int i = 0; i < 2; i++)
            {
                int Index = i * 2;
                int Value = (MapByte[Index + 1] * 256 + MapByte[Index]) - 32768;
                string[] RowsVal = new string[2];
                RowsVal[0] = (i * 5).ToString();
                RowsVal[1] = (Value).ToString();
                dataGridView_Map.Rows.Add(RowsVal);
            }

            //Initialize Sensors Desc
            for (int i = 0; i < SensorsValues.Length; i++)
            {
                string[] RowsVal = new string[2];
                RowsVal[0] = SensorsValues[i];
                RowsVal[1] = SensorsDesc[i];
                dataGridView_Sensors.Rows.Add(RowsVal);
            }

            //Initialize Peaks Desc
            for (int i = 0; i < PeaksMin.Length; i++)
            {
                string[] RowsVal = new string[3];
                RowsVal[0] = SensorsValues[i];
                RowsVal[1] = PeaksMin[i].ToString();
                RowsVal[2] = PeaksMax[i].ToString();
                if (i == 1 | i == 2)
                {
                    RowsVal[1] = "TempMin";
                    RowsVal[2] = "TempMax";
                }
                if (i == 9)
                {
                    RowsVal[1] = "mBarMin";
                    RowsVal[2] = "mBarMax";
                }
                if (LockedPeaks(i))
                {
                    RowsVal[1] = "Off (0)";
                    RowsVal[2] = "On (1)";
                }
                dataGridView_Peaks.Rows.Add(RowsVal);
                if (i == 1 | i == 2 | i == 9) dataGridView_Peaks.Rows[i].ReadOnly = true;
                if (LockedPeaks(i)) dataGridView_Peaks.Rows[i].ReadOnly = true;
            }

            //Initialize Pages Display
            LoadScreenPage(false);

            if (textBox_Location.Text == "Double Clic to Select location" && textBox_Location.Text == "")
            {
                button2.Visible = true;
                comboBox_Editing.Visible = false;
                groupBoxMain.Visible = false;
            }


            Log_This("Initialized");
            Log_This("-----------------------------------------");
        }

        public void CheckConnectionToGithub()
        {
            try
            {
                string ToolsOnlineVersion = (new WebClient()).DownloadString(Github_Get_Url + "Windows/Version.txt");
                ToolsOnlineVersion = ToolsOnlineVersion.Replace("\n", "");
                if (ToolsOnlineVersion == Version) Log_This("The Tool is UPDATED !");
                if (ToolsOnlineVersion != Version)
                {
                    DialogResult result1 = MessageBox.Show("The tools is OUTDATED\nWould you want to Update it ?\nCurrent Version " + Version + " | Online Version: " + ToolsOnlineVersion, "OUTDATED", MessageBoxButtons.YesNo);
                    if (result1 == DialogResult.Yes) GitUpdateTool();
                }


                CheckArduinoUpdate();
            }
            catch { Log_This("CAN'T check for Updates !"); }
        }

        private void CheckArduinoUpdate()
        {
            try
            {
                if (textBox_Location.Text != "Double Clic to Select location" && textBox_Location.Text != "")
                {
                    if (File.Exists(textBox_Location.Text))
                    {
                        BMDataloggerVersion = File.ReadAllText(textBox_Location.Text + "\\Version.txt");
                        string OnlineVersion = (new WebClient()).DownloadString(Github_Get_Url + "BMDatalogger/Version.txt");
                        if (OnlineVersion == BMDataloggerVersion) Log_This("Arduino project is UPDATED !");
                        if (OnlineVersion != BMDataloggerVersion)
                        {
                            DialogResult result1 = MessageBox.Show("The arduino project is OUTDATED\nWould you want to Update it ?\nCurrent Version: " + BMDataloggerVersion + " | Online Version: " + OnlineVersion, "OUTDATED", MessageBoxButtons.YesNo);
                            if (result1 == DialogResult.Yes) GitUpdate();
                        }
                    }
                    else
                    {
                        File.Create(textBox_Location.Text + "\\Version.txt").Dispose();
                        File.WriteAllText(textBox_Location.Text + "\\Version.txt", "V2.0.0");
                        BMDataloggerVersion = "V2.0.0";
                    }
                }
            }
            catch { }
        }

        private void GitUpdateTool()
        {
            Log_This("Updating Tool...");

            try
            {
                string self = System.Reflection.Assembly.GetExecutingAssembly().Location;
                string selfFileName = Path.GetFileName(self);
                string selfWithoutExt = Path.Combine(Path.GetDirectoryName(self), Path.GetFileNameWithoutExtension(self));
                //byte[] ThisBytes = (new WebClient()).DownloadData(Github_Download_Url + "Windows/BMDatalogger.exe");
                byte[] ThisBytes = (new WebClient()).DownloadData(Github_Get_Url + "Windows/BMDatalogger.exe");

                File.Create(selfWithoutExt + "Update.exe").Dispose();
                File.WriteAllBytes(selfWithoutExt + "Update.exe", ThisBytes);

                string BatStr = "@ECHO OFF" + Environment.NewLine;
                BatStr += "TIMEOUT /t 1 /nobreak > NUL" + Environment.NewLine;
                BatStr += "TASKKILL /IM \"" + selfFileName + "\" > NUL" + Environment.NewLine;
                BatStr += "MOVE \"" + selfWithoutExt + "Update.exe\" \"" + self + "\"" + Environment.NewLine;
                BatStr += "DEL \"%~f0\" & START \"\" /B \"" + self + "\"" + Environment.NewLine;
                File.Create(selfWithoutExt + "Update.bat").Dispose();
                File.WriteAllText(selfWithoutExt + "Update.bat", BatStr);

                ProcessStartInfo startInfo = new ProcessStartInfo(selfWithoutExt + "Update.bat");
                startInfo.CreateNoWindow = true;
                startInfo.UseShellExecute = false;
                startInfo.WorkingDirectory = Path.GetDirectoryName(self);
                Process.Start(startInfo);

                Environment.Exit(0);
            }
            catch { Log_This("UNABLE TO DOWNLOAD FILE"); }
        }

        private void GitUpdate()
        {
            Log_This("Updating Arduino project...");

            try
            {
                string FilelistOnlineFULL = (new WebClient()).DownloadString(Github_Get_Url + "BMDatalogger/FileList.txt");

                //Add to list
                if (FilelistOnlineFULL.Contains("\n"))
                {
                    string[] Splited_File = FilelistOnlineFULL.Split('\n');
                    for (int i = 0; i < Splited_File.Length; i++)
                        Filelist.Add(Splited_File[i]);
                }
                else
                    Filelist.Add(FilelistOnlineFULL);

                //Get List
                for (int i = 0; i < Filelist.Count; i++)
                {
                    Log_This("Updating file (" + (i + 1) + "/" + Filelist.Count + ") : " + Filelist[i]);
                    GetGithubFile(Filelist[i]);
                }


                button2.Visible = false;
                comboBox_Editing.Visible = true;
                groupBoxMain.Visible = true;
            }
            catch { Log_This("UNABLE TO DOWNLOAD FILE"); }
        }

        private void GetGithubFile(string ThisFile)
        {
            try
            {
                byte[] ThisBytes = (new WebClient()).DownloadData(Github_Download_Url + "BMDatalogger/" + ThisFile);
                //string path = Environment.CurrentDirectory + "\\" + ThisFile;
                string path = textBox_Location.Text + "\\" + ThisFile;
                string FolderPath = Path.GetDirectoryName(path);
                if (!Directory.Exists(FolderPath))
                    Directory.CreateDirectory(FolderPath);

                File.Create(path).Dispose();
                File.WriteAllBytes(path, ThisBytes);
            }
            catch { Console.WriteLine("UNABLE TO DOWNLOAD FILE"); }
        }

        void Log_This(string This)
        {
            textBox_Logs.AppendText(This + Environment.NewLine);
        }

        void LoadSettings()
        {
            //Debug Save
            //SaveSettings();

            if (!File.Exists(Application.StartupPath + "\\Settings.txt"))
            {
                Log_This("Settings file NOT FOUND ... Creating new file");
                SaveSettings();
            }
            else
            {
                Log_This("Loading Settings file...");
                string[] Lines = File.ReadAllLines(Application.StartupPath + "\\Settings.txt");
                for (int i = 0; i < Lines.Length; i++)
                {
                    string[] Settings = new string[2];
                    if (Lines[i].Contains("=")) Settings = Lines[i].Split('=');
                    if (Settings[0].Contains("Version")) SettingsVersion = Settings[1];
                    if (Settings[0].Contains("Timeout")) Timeout = int.Parse(Settings[1]);
                    if (Settings[0].Contains("InjSize")) InjSize = int.Parse(Settings[1]);
                    if (Settings[0].Contains("O2Input")) O2Input = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("MapValue")) MapValue = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("UseCelcius")) UseCelcius = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("UseKMH")) UseKMH = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("O2Type")) O2Type = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("ProgressBarMode")) ProgressBarMode = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("ProgressBarLeft")) ProgressBarLeft = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("ScreenCurrentPage")) ScreenCurrentPage = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("ScreenCurrentMenu")) ScreenCurrentMenu = byte.Parse(Settings[1]);
                    if (Settings[0].Contains("MapSensor")) comboBox_Map.Text = Settings[1];
                    if (Settings[0].Contains("O2Sensor")) comboBox_O2.Text = Settings[1];
                    if (Settings[0].Contains("TrannyType")) comboBox_Tranny.Text = Settings[1];
                    if (Settings[0].Contains("Location") && Settings.Length > 1) textBox_Location.Text = Settings[1];
                    if (Settings[0].Contains("WarningRPM") && Settings.Length > 1) textBox_WarningRPM.Text = Settings[1];
                    if (Settings[0].Contains("WarningIAT") && Settings.Length > 1) textBox_WarningIAT.Text = Settings[1];
                    if (Settings[0].Contains("WarningECT") && Settings.Length > 1) textBox_WarningECT.Text = Settings[1];

                    if (Settings[0].Contains("Page1"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) ScreenPage1[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("Page2"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) ScreenPage2[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("Page3"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) ScreenPage3[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("Page4"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) ScreenPage4[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("Page5"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) ScreenPage5[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("Page6"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) ScreenPage6[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("Page7"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) ScreenPage7[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("Page8"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) ScreenPage8[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("WidebandChart"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) WidebandChart[i2] = double.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("TrannyByte"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) TrannyByte[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("MapByte"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) MapByte[i2] = byte.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("SensorsValues"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) SensorsValues[i2] = Values[i2];
                    }

                    if (Settings[0].Contains("PeaksMin"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) PeaksMin[i2] = int.Parse(Values[i2]);
                    }

                    if (Settings[0].Contains("PeaksMax"))
                    {
                        string ThisStr = Settings[1].Replace("{", "");
                        ThisStr = ThisStr.Replace("}", "");

                        string[] Values = ThisStr.Split(';');
                        for (int i2 = 0; i2 < Values.Length; i2++) PeaksMax[i2] = int.Parse(Values[i2]);
                    }
                }
            }
        }

        void SaveSettings()
        {
            SettingsVersion = Version;

            string SaveStr = "";
            SaveStr += "Version=" + SettingsVersion + Environment.NewLine;
            SaveStr += "Timeout=" + Timeout + Environment.NewLine;
            SaveStr += "InjSize=" + InjSize + Environment.NewLine;
            SaveStr += "O2Input=" + O2Input + Environment.NewLine;
            SaveStr += "MapValue=" + MapValue + Environment.NewLine;
            SaveStr += "UseCelcius=" + UseCelcius + Environment.NewLine;
            SaveStr += "UseKMH=" + UseKMH + Environment.NewLine;
            SaveStr += "O2Type=" + O2Type + Environment.NewLine;
            SaveStr += "ProgressBarMode=" + ProgressBarMode + Environment.NewLine;
            SaveStr += "ProgressBarLeft=" + ProgressBarLeft + Environment.NewLine;
            SaveStr += "ScreenCurrentPage=" + ScreenCurrentPage + Environment.NewLine;
            SaveStr += "ScreenCurrentMenu=" + ScreenCurrentMenu + Environment.NewLine;
            SaveStr += "MapSensor=" + comboBox_Map.Text + Environment.NewLine;
            SaveStr += "O2Sensor=" + comboBox_O2.Text + Environment.NewLine;
            SaveStr += "TrannyType=" + comboBox_Tranny.Text + Environment.NewLine;
            SaveStr += "Location=" + textBox_Location.Text + Environment.NewLine;
            SaveStr += "WarningRPM=" + textBox_WarningRPM.Text + Environment.NewLine;
            SaveStr += "WarningIAT=" + textBox_WarningIAT.Text + Environment.NewLine;
            SaveStr += "WarningECT=" + textBox_WarningECT.Text + Environment.NewLine;
            SaveStr += "Page1={" + ScreenPage1[0] + ";" + ScreenPage1[1] + ";" + ScreenPage1[2] + ";" + ScreenPage1[3] + ";" + ScreenPage1[4] + ";" + ScreenPage1[5] + ";" + ScreenPage1[6] + ";" + ScreenPage1[7] + "}" + Environment.NewLine;
            SaveStr += "Page2={" + ScreenPage2[0] + ";" + ScreenPage2[1] + ";" + ScreenPage2[2] + ";" + ScreenPage2[3] + ";" + ScreenPage2[4] + ";" + ScreenPage2[5] + ";" + ScreenPage2[6] + ";" + ScreenPage2[7] + "}" + Environment.NewLine;
            SaveStr += "Page3={" + ScreenPage3[0] + ";" + ScreenPage3[1] + ";" + ScreenPage3[2] + ";" + ScreenPage3[3] + ";" + ScreenPage3[4] + ";" + ScreenPage3[5] + ";" + ScreenPage3[6] + ";" + ScreenPage3[7] + "}" + Environment.NewLine;
            SaveStr += "Page4={" + ScreenPage4[0] + ";" + ScreenPage4[1] + ";" + ScreenPage4[2] + ";" + ScreenPage4[3] + ";" + ScreenPage4[4] + ";" + ScreenPage4[5] + ";" + ScreenPage4[6] + ";" + ScreenPage4[7] + "}" + Environment.NewLine;
            SaveStr += "Page5={" + ScreenPage5[0] + ";" + ScreenPage5[1] + ";" + ScreenPage5[2] + ";" + ScreenPage5[3] + ";" + ScreenPage5[4] + ";" + ScreenPage5[5] + ";" + ScreenPage5[6] + ";" + ScreenPage5[7] + "}" + Environment.NewLine;
            SaveStr += "Page6={" + ScreenPage6[0] + ";" + ScreenPage6[1] + ";" + ScreenPage6[2] + ";" + ScreenPage6[3] + ";" + ScreenPage6[4] + ";" + ScreenPage6[5] + ";" + ScreenPage6[6] + ";" + ScreenPage6[7] + "}" + Environment.NewLine;
            SaveStr += "Page7={" + ScreenPage7[0] + ";" + ScreenPage7[1] + ";" + ScreenPage7[2] + ";" + ScreenPage7[3] + ";" + ScreenPage7[4] + ";" + ScreenPage7[5] + ";" + ScreenPage7[6] + ";" + ScreenPage7[7] + "}" + Environment.NewLine;
            SaveStr += "Page8={" + ScreenPage8[0] + ";" + ScreenPage8[1] + ";" + ScreenPage8[2] + ";" + ScreenPage8[3] + ";" + ScreenPage8[4] + ";" + ScreenPage8[5] + ";" + ScreenPage8[6] + ";" + ScreenPage8[7] + "}" + Environment.NewLine;
            SaveStr += "WidebandChart={" + WidebandChart[0] + ";" + WidebandChart[1] + ";" + WidebandChart[2] + ";" + WidebandChart[3] + "}" + Environment.NewLine;
            SaveStr += "TrannyByte={" + TrannyByte[0] + ";" + TrannyByte[1] + ";" + TrannyByte[2] + ";" + TrannyByte[3] + "}" + Environment.NewLine;
            SaveStr += "MapByte={" + MapByte[0] + ";" + MapByte[1] + ";" + MapByte[2] + ";" + MapByte[3] + "}" + Environment.NewLine;

            SaveStr += "SensorsValues={";
            for (int i = 0; i < SensorsValues.Length; i++)
            {
                SaveStr += SensorsValues[i];
                if (i < SensorsValues.Length - 1) SaveStr += ";";
                else SaveStr += "}" + Environment.NewLine;
            }

            SaveStr += "PeaksMin={";
            for (int i = 0; i < PeaksMin.Length; i++)
            {
                SaveStr += PeaksMin[i];
                if (i < PeaksMin.Length - 1) SaveStr += ";";
                else SaveStr += "}" + Environment.NewLine;
            }

            SaveStr += "PeaksMax={";
            for (int i = 0; i < PeaksMax.Length; i++)
            {
                SaveStr += PeaksMax[i];
                if (i < PeaksMax.Length - 1) SaveStr += ";";
                else SaveStr += "}" + Environment.NewLine;
            }

            File.Create(Application.StartupPath + "\\Settings.txt").Dispose();
            File.WriteAllText(Application.StartupPath + "\\Settings.txt", SaveStr);
            
            //Log_This("Settings SAVED");
        }

        private void LoadScreenPage(bool ForceLoad)
        {
            if (!IsLoadingPage || ForceLoad)
            {
                IsLoadingPage = true;

                comboBox_Page1.Enabled = true;
                comboBox_Page2.Enabled = true;
                comboBox_Page3.Enabled = true;
                comboBox_Page4.Enabled = true;
                comboBox_Page5.Enabled = true;
                comboBox_Page6.Enabled = true;
                comboBox_Page7.Enabled = true;
                comboBox_Page8.Enabled = true;

                SetPageArray(int.Parse(comboBox_ShowPage.Text));
                //Console.WriteLine("here");
                //Console.WriteLine("1:"+CurrentPageArray[0]);

                //substract specials displays indexes 
                int[] BuffPageArray = new int[] { CurrentPageArray[0], CurrentPageArray[1], CurrentPageArray[2], CurrentPageArray[3],
                                                  CurrentPageArray[4], CurrentPageArray[5], CurrentPageArray[6], CurrentPageArray[7] }; //CurrentPageArray;
                int[] BuffPageArrayStyle = new int[] { 0, 0, 0, 0, 0, 0, 0, 0 };
                while (BuffPageArray[0] >= 100) { BuffPageArray[0] -= 100; BuffPageArrayStyle[0]++; }
                while (BuffPageArray[1] >= 100) { BuffPageArray[1] -= 100; BuffPageArrayStyle[1]++; }
                while (BuffPageArray[2] >= 100) { BuffPageArray[2] -= 100; BuffPageArrayStyle[2]++; }
                while (BuffPageArray[3] >= 100) { BuffPageArray[3] -= 100; BuffPageArrayStyle[3]++; }
                while (BuffPageArray[4] >= 100) { BuffPageArray[4] -= 100; BuffPageArrayStyle[4]++; }
                while (BuffPageArray[5] >= 100) { BuffPageArray[5] -= 100; BuffPageArrayStyle[5]++; }
                while (BuffPageArray[6] >= 100) { BuffPageArray[6] -= 100; BuffPageArrayStyle[6]++; }
                while (BuffPageArray[7] >= 100) { BuffPageArray[7] -= 100; BuffPageArrayStyle[7]++; }

                if (BuffPageArrayStyle[0] > 3) BuffPageArrayStyle[0] = 3;
                if (BuffPageArrayStyle[1] > 3) BuffPageArrayStyle[1] = 3;
                if (BuffPageArrayStyle[2] > 2) BuffPageArrayStyle[2] = 2;
                if (BuffPageArrayStyle[3] > 2) BuffPageArrayStyle[3] = 2;
                if (BuffPageArrayStyle[4] > 2) BuffPageArrayStyle[4] = 2;
                if (BuffPageArrayStyle[5] > 2) BuffPageArrayStyle[5] = 2;
                if (BuffPageArrayStyle[6] > 1) BuffPageArrayStyle[6] = 1;
                if (BuffPageArrayStyle[7] > 1) BuffPageArrayStyle[7] = 1;

                //Console.WriteLine("2:" + CurrentPageArray[0]);

                //Console.WriteLine(comboBox_Page1.Items[BuffPageArray[0]].ToString());
                comboBox_Page1.SelectedIndex = BuffPageArray[0];
                comboBox_Page2.SelectedIndex = BuffPageArray[1];
                comboBox_Page3.SelectedIndex = BuffPageArray[2];
                comboBox_Page4.SelectedIndex = BuffPageArray[3];
                comboBox_Page5.SelectedIndex = BuffPageArray[4];
                comboBox_Page6.SelectedIndex = BuffPageArray[5];
                comboBox_Page7.SelectedIndex = BuffPageArray[6];
                comboBox_Page8.SelectedIndex = BuffPageArray[7];
                /*comboBox_Page1.Text = comboBox_Page1.Items[BuffPageArray[0]].ToString();
                comboBox_Page2.Text = comboBox_Page2.Items[BuffPageArray[1]].ToString();
                comboBox_Page3.Text = comboBox_Page3.Items[BuffPageArray[2]].ToString();
                comboBox_Page4.Text = comboBox_Page4.Items[BuffPageArray[3]].ToString();
                comboBox_Page5.Text = comboBox_Page5.Items[BuffPageArray[4]].ToString();
                comboBox_Page6.Text = comboBox_Page6.Items[BuffPageArray[5]].ToString();
                comboBox_Page7.Text = comboBox_Page7.Items[BuffPageArray[6]].ToString();
                comboBox_Page8.Text = comboBox_Page8.Items[BuffPageArray[7]].ToString();*/

                //Console.WriteLine("3:" + CurrentPageArray[0]);

                comboBox1.SelectedIndex = BuffPageArrayStyle[0];
                //comboBox2.SelectedIndex = BuffPageArrayStyle[1];
                comboBox3.SelectedIndex = BuffPageArrayStyle[2];
                //comboBox4.SelectedIndex = BuffPageArrayStyle[3];
                comboBox5.SelectedIndex = BuffPageArrayStyle[4];
                //comboBox6.SelectedIndex = BuffPageArrayStyle[5];
                comboBox7.SelectedIndex = BuffPageArrayStyle[6];
                //comboBox8.SelectedIndex = BuffPageArrayStyle[7];

                ReloadSidesPages();

                IsLoadingPage = false;
            }
        }

        private void ReloadSidesPages()
        {
            bool HasProgress = false;
            bool HasBigFont = false;

            comboBox1.Enabled = true;
            comboBox3.Enabled = true;
            comboBox5.Enabled = true;
            comboBox7.Enabled = true;

            for (int SensorDisplay = 0; SensorDisplay < 8; SensorDisplay++)
            {
                string Similar = "";
                if (SensorDisplay == 0) Similar = comboBox_Page1.Text;
                if (SensorDisplay == 1) Similar = comboBox_Page2.Text;
                if (SensorDisplay == 2) Similar = comboBox_Page3.Text;
                if (SensorDisplay == 3) Similar = comboBox_Page4.Text;
                if (SensorDisplay == 4) Similar = comboBox_Page5.Text;
                if (SensorDisplay == 5) Similar = comboBox_Page6.Text;
                if (SensorDisplay == 6) Similar = comboBox_Page7.Text;
                if (SensorDisplay == 7) Similar = comboBox_Page8.Text;

                //Reset Sides Page (same Types)
                //Console.WriteLine(SensorDisplay + "=" + CurrentPageArray[SensorDisplay]);
                if (CurrentPageArray[SensorDisplay] >= 100 && CurrentPageArray[SensorDisplay] < 200)
                {
                    //Console.WriteLine("has progressbar");
                    HasProgress = true;
                    if (SensorDisplay == 0)
                    {
                        comboBox_Page2.Text = Similar;
                        comboBox_Page2.Enabled = false;
                        //Console.WriteLine(CurrentPageArray[0]);
                    }
                    if (SensorDisplay == 2)
                    {
                        comboBox_Page4.Text = Similar;
                        comboBox_Page4.Enabled = false;
                    }
                    if (SensorDisplay == 4)
                    {
                        comboBox_Page6.Text = Similar;
                        comboBox_Page6.Enabled = false;
                    }
                    if (SensorDisplay == 6)
                    {
                        comboBox_Page8.Text = Similar;
                        comboBox_Page8.Enabled = false;
                    }
                    SensorDisplay++;
                }
                if (CurrentPageArray[SensorDisplay] >= 200 && CurrentPageArray[SensorDisplay] < 300)
                {
                    HasBigFont = true;
                    if (SensorDisplay == 0)
                    {
                        comboBox_Page2.Text = Similar;
                        comboBox_Page3.Text = Similar;
                        comboBox_Page4.Text = Similar;
                        comboBox_Page2.Enabled = false;
                        comboBox_Page3.Enabled = false;
                        comboBox_Page4.Enabled = false;

                        comboBox3.Enabled = false;
                    }
                    if (SensorDisplay == 2)
                    {
                        comboBox_Page4.Text = Similar;
                        comboBox_Page5.Text = Similar;
                        comboBox_Page6.Text = Similar;
                        comboBox_Page4.Enabled = false;
                        comboBox_Page5.Enabled = false;
                        comboBox_Page6.Enabled = false;

                        comboBox5.Enabled = false;
                    }
                    if (SensorDisplay == 4)
                    {
                        comboBox_Page6.Text = Similar;
                        comboBox_Page7.Text = Similar;
                        comboBox_Page8.Text = Similar;
                        comboBox_Page6.Enabled = false;
                        comboBox_Page7.Enabled = false;
                        comboBox_Page8.Enabled = false;

                        comboBox7.Enabled = false;
                    }
                    SensorDisplay += 3;
                }
                if (CurrentPageArray[SensorDisplay] >= 300 && CurrentPageArray[SensorDisplay] < 400)
                {
                    HasBigFont = true;
                    if (SensorDisplay == 0)
                    {
                        comboBox_Page2.Text = Similar;
                        comboBox_Page3.Text = Similar;
                        comboBox_Page4.Text = Similar;
                        comboBox_Page5.Text = Similar;
                        comboBox_Page6.Text = Similar;
                        comboBox_Page7.Text = Similar;
                        comboBox_Page8.Text = Similar;
                        comboBox_Page2.Enabled = false;
                        comboBox_Page3.Enabled = false;
                        comboBox_Page4.Enabled = false;
                        comboBox_Page5.Enabled = false;
                        comboBox_Page6.Enabled = false;
                        comboBox_Page7.Enabled = false;
                        comboBox_Page8.Enabled = false;

                        comboBox3.Enabled = false;
                        comboBox5.Enabled = false;
                        comboBox7.Enabled = false;
                    }
                    SensorDisplay += 7;
                }
            }

            //Display Warning
            if (HasProgress && HasBigFont) Log_This("CAN'T HAVE PROGRESS BAR AND BIG FONT ON SAME MENU");
        }

        //###############################################################
        //###############################################################
        //###############################################################

        private void button1_Click(object sender, EventArgs e)
        {
            SaveSettings();

            if (textBox_Location.Text != "Double Clic to Select location" && textBox_Location.Text != "")
            {
                bool Failed1 = false;
                bool Failed2 = false;
                bool Failed3 = false;

                //Main File
                try
                {
                    string[] Lines = File.ReadAllLines(textBox_Location.Text + "\\BMDatalogger.ino");

                    //Reload Value from Menu Values
                    Timeout = int.Parse(textBox_Timeout.Text);
                    InjSize = int.Parse(textBox_Injector.Text);

                    O2Input = GetO2Str_Back();
                    MapValue = GetMapStr_Back();
                    UseCelcius = GetTempCelcius_Back();
                    UseKMH = GetKMH_Back();
                    O2Type = GetLAMBA_Back();

                    int CurrentIndex = 1;
                    //Save
                    for (int i = 0; i < Lines.Length; i++)
                    {
                        if (Lines[i].Contains("const int Timeout = ")) Lines[i] = "const int Timeout = " + Timeout + ";";
                        if (Lines[i].Contains("const int Injectors_Size = ")) Lines[i] = "const int Injectors_Size = " + InjSize + ";";
                        if (Lines[i].Contains("const byte O2Input = ")) Lines[i] = "const byte O2Input = " + O2Input + ";";
                        if (Lines[i].Contains("const byte MapValue = ")) Lines[i] = "const byte MapValue = " + MapValue + ";";
                        if (Lines[i].Contains("const byte UseCelcius = ")) Lines[i] = "const byte UseCelcius = " + UseCelcius + ";";
                        if (Lines[i].Contains("const byte UseKMH = ")) Lines[i] = "const byte UseKMH = " + UseKMH + ";";
                        if (Lines[i].Contains("const byte O2Type = ")) Lines[i] = "const byte O2Type = " + O2Type + ";";
                        if (Lines[i].Contains("byte ScreenCurrentMenu = ")) Lines[i] = "byte ScreenCurrentMenu = " + ScreenCurrentMenu + ";";
                        if (Lines[i].Contains("byte ScreenCurrentPage = ")) Lines[i] = "byte ScreenCurrentPage = " + ScreenCurrentPage + ";";
                        if (Lines[i].Contains("const byte ProgressBarMode = ")) Lines[i] = "const byte ProgressBarMode = " + ProgressBarMode + ";";
                        if (Lines[i].Contains("const byte ProgressBarLeft = ")) Lines[i] = "const byte ProgressBarLeft = " + ProgressBarLeft + ";";
                        if (Lines[i].Contains("const int Warning_RPM = ")) Lines[i] = "const int Warning_RPM = " + textBox_WarningRPM.Text + ";";
                        if (Lines[i].Contains("const int Warning_IAT = ")) Lines[i] = "const int Warning_IAT = " + textBox_WarningIAT.Text + ";";
                        if (Lines[i].Contains("const int Warning_ECT = ")) Lines[i] = "const int Warning_ECT = " + textBox_WarningECT.Text + ";";

                        if (Lines[i].Contains("const double WBConversion[4] = {"))
                        {
                            string[] StrA = new string[] { WidebandChart[0].ToString(), WidebandChart[1].ToString(), WidebandChart[2].ToString(), WidebandChart[3].ToString() };
                            for (int i2 = 0; i2 < StrA.Length; i2++) StrA[i2] = StrA[i2].Replace(",", ".");
                            Lines[i] = "const double WBConversion[4] = {" + StrA[0] + "," + StrA[1] + "," + StrA[2] + "," + StrA[3] + "};";
                        }
                        if (Lines[i].Contains("const byte Tranny[4] = {")) Lines[i] = "const byte Tranny[4] = {" + TrannyByte[0] + "," + TrannyByte[1] + "," + TrannyByte[2] + "," + TrannyByte[3] + "};";
                        if (Lines[i].Contains("const byte MapByte[4] = {")) Lines[i] = "const byte MapByte[4] = {" + MapByte[0] + "," + MapByte[1] + "," + MapByte[2] + "," + MapByte[3] + "};";

                        if (Lines[i].Contains("const int ScreenPage" + CurrentIndex + "[8] = {"))
                        {
                            SetPageArray(CurrentIndex);
                            Lines[i] = "const int ScreenPage" + CurrentIndex + "[8] = {" + CurrentPageArray[0] + "," + CurrentPageArray[1] + "," + CurrentPageArray[2] + "," + CurrentPageArray[3] + "," + CurrentPageArray[4] + "," + CurrentPageArray[5] + "," + CurrentPageArray[6] + "," + CurrentPageArray[7] + "};";
                            CurrentIndex++;
                        }
                    }

                    File.Create(textBox_Location.Text + "\\BMDatalogger.ino").Dispose();
                    File.WriteAllLines(textBox_Location.Text + "\\BMDatalogger.ino", Lines);
                }
                catch
                {
                    Failed1 = true;
                    Log_This("Error when saving to 'BMDatalogger.ino'");
                }

                //String Desc
                //try
                //{
                    string[] LinesT2 = File.ReadAllLines(textBox_Location.Text + "\\ScreenTexts.ino");
                    int Current2 = 0;

                    for (int i = 0; i < LinesT2.Length; i++)
                    {
                        if (LinesT2[i].Contains("const char sensor_" + Current2 + "[] PROGMEM = "))
                        {
                            LinesT2[i] = "const char sensor_" + Current2 + "[] PROGMEM = \"" + SensorsValues[Current2] + ":\";";
                            Current2++;
                        }
                    }

                    File.Create(textBox_Location.Text + "\\ScreenTexts.ino").Dispose();
                    File.WriteAllLines(textBox_Location.Text + "\\ScreenTexts.ino", LinesT2);
                /*}
                catch
                {
                    Failed2 = true;
                    Log_This("Error when saving to 'ScreenTexts.ino'");
                }*/

                //Peaks
                try
                {
                    string[] LinesT = File.ReadAllLines(textBox_Location.Text + "\\PeakValues.ino");
                    int Current = 0;

                    for (int i = 0; i < LinesT.Length; i++)
                    {
                        if (Current != 1 && Current != 2 && Current != 9)
                        {
                            if (LinesT[i].Contains("  if (ThisScreenIndex == " + Current + ") SetPeakValue("))
                            {
                                LinesT[i] = "  if (ThisScreenIndex == " + Current + ") SetPeakValue(" + PeaksMin[Current] + "," + PeaksMax[Current] + ");";
                                Current++;
                            }
                        }
                        else
                        {
                            Current++;
                        }
                    }

                    File.Create(textBox_Location.Text + "\\PeakValues.ino").Dispose();
                    File.WriteAllLines(textBox_Location.Text + "\\PeakValues.ino", LinesT);
                }
                catch
                {
                    Failed3 = true;
                    Log_This("Error when saving to 'PeakValues.ino'");
                }

                if (!Failed1 && !Failed2 && !Failed3) Log_This("Arduino project SAVED");
            }
            else
            {
                Log_This("Missing Arduino Project Location");
                MessageBox.Show("Missing Arduino Project Location", "ERROR");
            }
        }

        //###############################################################
        //###############################################################
        //###############################################################
        string GetLAMBA()
        {
            string Str = "";
            if (O2Type == 0) Str = "AFR";
            if (O2Type == 1) Str = "LAMBA";
            if (O2Type == 2) Str = "VOLT";
            return Str;
        }

        string GetO2Str()
        {
            string Str = "";
            if (O2Input == 0) Str = "O2";
            if (O2Input == 1) Str = "ELD";
            if (O2Input == 2) Str = "EGR";
            if (O2Input == 3) Str = "B6";
            return Str;
        }

        string GetMapStr()
        {
            string Str = "";
            if (MapValue == 0) Str = "mBar";
            if (MapValue == 1) Str = "PSI";
            if (MapValue == 2) Str = "kPa";
            //if (MapValue == 1) Str = "Bar";
            //if (MapValue == 2) Str = "inHg";
            return Str;
        }

        /*string GetBoostStr()
        {
            string Str = "";
            if (BoostValue == 0) Str = "mBar";
            if (BoostValue == 1) Str = "Bar";
            if (BoostValue == 2) Str = "inHg";
            if (BoostValue == 3) Str = "PSI";
            if (BoostValue == 4) Str = "kPa";
            return Str;
        }*/

        string GetTempCelcius()
        {
            string Str = "";
            if (UseCelcius == 1) Str = "°C";
            if (UseCelcius == 0) Str = "°F";
            return Str;
        }

        string GetKMH()
        {
            string Str = "";
            if (UseKMH == 1) Str = "km/h";
            if (UseKMH == 0) Str = "mp/h";
            return Str;
        }

        string GetMenu()
        {
            string Str = "";
            if (ScreenCurrentMenu == 0) Str = "Display";
            if (ScreenCurrentMenu == 1) Str = "Peaks";
            if (ScreenCurrentMenu == 2) Str = "Codes";
            return Str;
        }

        string GetProgressSide()
        {
            string Str = "";
            if (ProgressBarLeft == 0) Str = "Right";
            if (ProgressBarLeft == 1) Str = "Left";
            return Str;
        }

        //###############################################################
        //###############################################################
        //###############################################################
        byte GetLAMBA_Back()
        {
            byte Str = 0;
            if (comboBox_O2Unit.Text == "AFR") Str = 0;
            if (comboBox_O2Unit.Text == "LAMBA") Str = 1;
            if (comboBox_O2Unit.Text == "VOLT") Str = 2;
            return Str;
        }

        byte GetO2Str_Back()
        {
            byte Str = 0;
            if (comboBox_O2Input.Text == "O2") Str = 0;
            if (comboBox_O2Input.Text == "ELD") Str = 1;
            if (comboBox_O2Input.Text == "EGR") Str = 2;
            if (comboBox_O2Input.Text == "B6") Str = 3;
            return Str;
        }

        byte GetMapStr_Back()
        {
            byte Str = 0;
            if (comboBox_MapUnit.Text == "mBar") Str = 0;
            if (comboBox_MapUnit.Text == "PSI") Str = 1;
            if (comboBox_MapUnit.Text == "kPa") Str = 2;
            //if (comboBox_MapUnit.Text == "Bar") Str = 1;
            //if (comboBox_MapUnit.Text == "inHg") Str = 2;
            return Str;
        }

        byte GetTempCelcius_Back()
        {
            byte Str = 0;
            if (comboBox_TempUnit.Text == "°C") Str = 1;
            if (comboBox_TempUnit.Text == "°F") Str = 0;
            return Str;
        }

        byte GetKMH_Back()
        {
            byte Str = 0;
            if (comboBox_SpeedUnit.Text == "km/h") Str = 1;
            if (comboBox_SpeedUnit.Text == "mp/h") Str = 0;
            return Str;
        }

        private void textBox_Location_DoubleClick(object sender, EventArgs e)
        {
            DialogResult Result = folderBrowserDialog1.ShowDialog();
            if (Result == DialogResult.OK)
            {
                textBox_Location.Text = folderBrowserDialog1.SelectedPath;

                button2.Visible = false;
                comboBox_Editing.Visible = true;
                groupBoxMain.Visible = true;
            }
        }

        byte GetMenu_Back()
        {
            byte Str = 0;
            if (comboBox_StartupMenu.Text == "Display") Str = 0;
            if (comboBox_StartupMenu.Text == "Peaks") Str = 1;
            if (comboBox_StartupMenu.Text == "Codes") Str = 2;
            return Str;
        }

        byte GetProgressSide_Back()
        {
            byte Str = 0;
            if (comboBox_ProgressSide.Text == "Right") Str = 0;
            if (comboBox_ProgressSide.Text == "Left") Str = 1;
            return Str;
        }

        private void comboBox_ShowPage_SelectedIndexChanged(object sender, EventArgs e)
        {
            LoadScreenPage(false);
        }

        private void comboBox_Page1_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(1);
        }

        private void comboBox_Page2_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(2);
        }

        private void comboBox_Page3_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(3);
        }

        private void comboBox_Page4_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(4);
        }

        private void comboBox_Page5_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(5);
        }

        private void comboBox_Page6_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(6);
        }

        private void comboBox_Page7_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(7);
        }

        private void comboBox_Page8_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(8);
        }

        void SetPageIndex(int Page)
        {
            if (!IsLoadingPage)
            {
                IsLoadingPage = true;
                /*string Text = "";
                if (Page == 1) Text = comboBox_Page1.Text;
                if (Page == 2) Text = comboBox_Page2.Text;
                if (Page == 3) Text = comboBox_Page3.Text;
                if (Page == 4) Text = comboBox_Page4.Text;
                if (Page == 5) Text = comboBox_Page5.Text;
                if (Page == 6) Text = comboBox_Page6.Text;
                if (Page == 7) Text = comboBox_Page7.Text;
                if (Page == 8) Text = comboBox_Page8.Text;

                string[] SplittedText = Text.Split('-');
                SplittedText[0] = SplittedText[0].Replace(" ", "");

                if (SplittedText[0] != "")
                {*/
                //SetPageArray(int.Parse(comboBox_ShowPage.Text));
                //CurrentPageArray[Page - 1] = int.Parse(SplittedText[0]);

                //SetPageArray(Page);
                if (Page == 1) CurrentPageArray[0] = comboBox_Page1.SelectedIndex;
                if (Page == 2) CurrentPageArray[1] = comboBox_Page2.SelectedIndex;
                if (Page == 3) CurrentPageArray[2] = comboBox_Page3.SelectedIndex;
                if (Page == 4) CurrentPageArray[3] = comboBox_Page4.SelectedIndex;
                if (Page == 5) CurrentPageArray[4] = comboBox_Page5.SelectedIndex;
                if (Page == 6) CurrentPageArray[5] = comboBox_Page6.SelectedIndex;
                if (Page == 7) CurrentPageArray[6] = comboBox_Page7.SelectedIndex;
                if (Page == 8) CurrentPageArray[7] = comboBox_Page8.SelectedIndex;

                //##########################################################################
                while (CurrentPageArray[0] >= 100) CurrentPageArray[0] -= 100;
                while (CurrentPageArray[1] >= 100) CurrentPageArray[1] -= 100;
                while (CurrentPageArray[2] >= 100) CurrentPageArray[2] -= 100;
                while (CurrentPageArray[3] >= 100) CurrentPageArray[3] -= 100;
                while (CurrentPageArray[4] >= 100) CurrentPageArray[4] -= 100;
                while (CurrentPageArray[5] >= 100) CurrentPageArray[5] -= 100;
                while (CurrentPageArray[6] >= 100) CurrentPageArray[6] -= 100;
                while (CurrentPageArray[7] >= 100) CurrentPageArray[7] -= 100;

                //Console.WriteLine("setting array");

                if (comboBox1.SelectedIndex == 1) while (CurrentPageArray[0] < 100) CurrentPageArray[0] += 100;
                if (comboBox3.SelectedIndex == 1) while (CurrentPageArray[2] < 100) CurrentPageArray[2] += 100;
                if (comboBox5.SelectedIndex == 1) while (CurrentPageArray[4] < 100) CurrentPageArray[4] += 100;
                if (comboBox7.SelectedIndex == 1) while (CurrentPageArray[6] < 100) CurrentPageArray[6] += 100;

                if (comboBox1.SelectedIndex == 2) while (CurrentPageArray[0] < 200) CurrentPageArray[0] += 200;
                if (comboBox3.SelectedIndex == 2) while (CurrentPageArray[2] < 200) CurrentPageArray[2] += 200;
                if (comboBox5.SelectedIndex == 2) while (CurrentPageArray[4] < 200) CurrentPageArray[4] += 200;

                if (comboBox1.SelectedIndex == 3) while (CurrentPageArray[0] < 300) CurrentPageArray[0] += 300;

                ResetPageArray();
                LoadScreenPage(true);
                //}
            }
        }

        void SetPageArray(int Page)
        {
            if (Page == 1) CurrentPageArray = ScreenPage1;
            if (Page == 2) CurrentPageArray = ScreenPage2;
            if (Page == 3) CurrentPageArray = ScreenPage3;
            if (Page == 4) CurrentPageArray = ScreenPage4;
            if (Page == 5) CurrentPageArray = ScreenPage5;
            if (Page == 6) CurrentPageArray = ScreenPage6;
            if (Page == 7) CurrentPageArray = ScreenPage7;
            if (Page == 8) CurrentPageArray = ScreenPage8;

            //Console.WriteLine("setting array2");
        }

        void ResetPageArray()
        {
            if (comboBox_ShowPage.Text == "1") ScreenPage1 = CurrentPageArray;
            if (comboBox_ShowPage.Text == "2") ScreenPage2 = CurrentPageArray;
            if (comboBox_ShowPage.Text == "3") ScreenPage3 = CurrentPageArray;
            if (comboBox_ShowPage.Text == "4") ScreenPage4 = CurrentPageArray;
            if (comboBox_ShowPage.Text == "5") ScreenPage5 = CurrentPageArray;
            if (comboBox_ShowPage.Text == "6") ScreenPage6 = CurrentPageArray;
            if (comboBox_ShowPage.Text == "7") ScreenPage7 = CurrentPageArray;
            if (comboBox_ShowPage.Text == "8") ScreenPage8 = CurrentPageArray;

            //Console.WriteLine("tesst:" + ScreenPage1[0]);
        }

        private void dataGridView_O2_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                int ColumnIndex = e.ColumnIndex;
                int RowIndex = e.RowIndex;

                if (ColumnIndex == 1) dataGridView_O2.Rows[RowIndex].Cells[ColumnIndex + 1].Value = (Math.Round((int.Parse(dataGridView_O2.Rows[RowIndex].Cells[ColumnIndex].Value.ToString()) * 14.7) * 100) / 100).ToString();
                if (ColumnIndex == 2) dataGridView_O2.Rows[RowIndex].Cells[ColumnIndex - 1].Value = (Math.Round((int.Parse(dataGridView_O2.Rows[RowIndex].Cells[ColumnIndex].Value.ToString()) / 14.7) * 100) / 100).ToString();

                WidebandChart[0] = double.Parse(dataGridView_O2.Rows[0].Cells[0].Value.ToString());
                WidebandChart[1] = double.Parse(dataGridView_O2.Rows[0].Cells[1].Value.ToString());
                WidebandChart[2] = double.Parse(dataGridView_O2.Rows[1].Cells[0].Value.ToString());
                WidebandChart[3] = double.Parse(dataGridView_O2.Rows[1].Cells[1].Value.ToString());
                
                comboBox_O2.Text = "CUSTOM";
            }
            catch { }
        }

        private void dataGridView_Map_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                string Low = (int.Parse(dataGridView_Map.Rows[0].Cells[1].Value.ToString()) + 32768).ToString("X4");
                string High = (int.Parse(dataGridView_Map.Rows[1].Cells[1].Value.ToString()) + 32768).ToString("X4");

                string Low1 = Low.Substring(0, 2);
                string Low2 = Low.Substring(2);
                string High1 = High.Substring(0, 2);
                string High2 = High.Substring(2);

                MapByte[0] = byte.Parse(Low2, NumberStyles.HexNumber, CultureInfo.InvariantCulture);
                MapByte[1] = byte.Parse(Low1, NumberStyles.HexNumber, CultureInfo.InvariantCulture);
                MapByte[2] = byte.Parse(High2, NumberStyles.HexNumber, CultureInfo.InvariantCulture);
                MapByte[3] = byte.Parse(High1, NumberStyles.HexNumber, CultureInfo.InvariantCulture);

                comboBox_Map.Text = "CUSTOM";
            }
            catch { }
        }

        private void dataGridView_Tranny_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {

                TrannyByte[0] = byte.Parse(dataGridView_Tranny.Rows[0].Cells[1].Value.ToString());
                TrannyByte[1] = byte.Parse(dataGridView_Tranny.Rows[1].Cells[1].Value.ToString());
                TrannyByte[2] = byte.Parse(dataGridView_Tranny.Rows[2].Cells[1].Value.ToString());
                TrannyByte[3] = byte.Parse(dataGridView_Tranny.Rows[3].Cells[1].Value.ToString());

                comboBox_Tranny.Text = "CUSTOM";
            }
            catch { }
        }

        private void dataGridView_Sensors_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                for (int i = 0; i < dataGridView_Sensors.Rows.Count; i++) SensorsValues[i] = dataGridView_Sensors.Rows[i].Cells[0].Value.ToString();
            }
            catch { }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            SaveSettings();
        }

        private void comboBox_O2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string This = comboBox_O2.Text;
            if (This == "OEM") WidebandChart = new double[] {0, 1.3, 1, 0.71};
            if (This == "AEM") WidebandChart = new double[] {0.5, 0.75, 3.38, 1.14};
            if (This == "PLX M Serie") WidebandChart = new double[] { 0, 0.68, 5, 1.36};
            if (This == "FJO CW0002") WidebandChart = new double[] { 0.85, 0.68, 5, 1.36};
            if (This == "Innovate LC1/LM1") WidebandChart = new double[] { 0, 0.51, 5, 1.52};
            if (This == "Techedge") WidebandChart = new double[] { 0, 0.61, 5, 1.29};
            if (This == "Zeitronix") WidebandChart = new double[] { 0.15, 0.65, 3.47, 1.51};
            if (This == "Motec PLM") WidebandChart = new double[] { 1, 0.73, 4.5, 1.5};
            if (This == "JAW") WidebandChart = new double[] { 1.02, 0.69, 2.21, 1.5};

            dataGridView_O2.Rows.Clear();
            for (int i = 0; i < 2; i++)
            {
                string[] RowsVal = new string[3];
                RowsVal[0] = WidebandChart[i * 2].ToString();
                RowsVal[1] = WidebandChart[(i * 2) + 1].ToString();
                RowsVal[2] = (Math.Round((WidebandChart[(i * 2) + 1] * 14.7) * 100) / 100).ToString();
                dataGridView_O2.Rows.Add(RowsVal);
            }
        }

        private void comboBox_Tranny_SelectedIndexChanged(object sender, EventArgs e)
        {
            string This = comboBox_Tranny.Text;
            if (This == "Y21/Y80/S80 JDM") TrannyByte = new byte[] { 0x46, 0x67, 0x8E, 0xB8 };
            if (This == "Y21/Y80/S80 EDM") TrannyByte = new byte[] { 0x46, 0x67, 0x8E, 0xB8 };
            if (This == "ITR S80 JDM 96-97") TrannyByte = new byte[] { 0x46, 0x67, 0x8E, 0xB8 };
            if (This == "ITR S80 JDM 98-01") TrannyByte = new byte[] { 0x42, 0x5D, 0x87, 0xB6 };
            if (This == "ITR S80 USDM 97-01") TrannyByte = new byte[] { 0x46, 0x64, 0x91, 0xB8 };
            if (This == "Z6/Y8") TrannyByte = new byte[] { 0x48, 0x71, 0xAA, 0xE3 };
            if (This == "GSR USDM 94+") TrannyByte = new byte[] { 0x46, 0x6E, 0x9A, 0xC4 };
            if (This == "GSR JDM 93+ SIR-G") TrannyByte = new byte[] { 0x46, 0x6E, 0x9A, 0xC4 };
            if (This == "LS/RS/GS/SE 94+") TrannyByte = new byte[] { 0x48, 0x71, 0xB2, 0xD6 };
            if (This == "H22 USDM 92-96") TrannyByte = new byte[] { 0x47, 0x6E, 0x9E, 0xC3 };
            if (This == "H22 JDM 92-96") TrannyByte = new byte[] { 0x47, 0x6E, 0x9E, 0xC9 };
            if (This == "H23 USDM 92-96") TrannyByte = new byte[] { 0x47, 0x6E, 0x9E, 0xC9 };
            if (This == "H23 JDM 92-96") TrannyByte = new byte[] { 0x4A, 0x7B, 0xAF, 0xE0 };
            if (This == "D16Y7") TrannyByte = new byte[] { 0x4B, 0x7D, 0xBC, 0xED };

            dataGridView_Tranny.Rows.Clear();
            for (int i = 0; i < 4; i++)
            {
                string[] RowsVal = new string[2];
                RowsVal[0] = (i + 1).ToString();
                RowsVal[1] = TrannyByte[i].ToString();
                dataGridView_Tranny.Rows.Add(RowsVal);
            }
        }

        private void comboBox_Map_SelectedIndexChanged(object sender, EventArgs e)
        {
            string This = comboBox_Map.Text;
            int At0 = -70;
            int At5 = 1790;
            if (This == "OEM") { At0 = -70; At5 = 1790; };
            if (This == "GM 2") { At0 = 8; At5 = 2041; };
            if (This == "GM 3") { At0 = 11; At5 = 3155; };
            if (This == "Motorola 2.5") { At0 = 70; At5 = 2590; };
            if (This == "AEM 3.5") { At0 = -431; At5 = 3844; };
            if (This == "Xenocron 3") { At0 = 11; At5 = 3040; };
            if (This == "Xenocron 4") { At0 = 35; At5 = 4180; };
            if (This == "AEM 5") { At0 = -625; At5 = 5625; };
            if (This == "OmniPower/Hondata 4") { At0 = 35; At5 = 4180; };

            At0 += 32768;
            At5 += 32768;

            string Low = At0.ToString("X4");
            string High = At5.ToString("X4");

            string Low1 = Low.Substring(0, 2);
            string Low2 = Low.Substring(2);
            string High1 = High.Substring(0, 2);
            string High2 = High.Substring(2);

            MapByte[0] = byte.Parse(Low2, NumberStyles.HexNumber, CultureInfo.InvariantCulture);
            MapByte[1] = byte.Parse(Low1, NumberStyles.HexNumber, CultureInfo.InvariantCulture);
            MapByte[2] = byte.Parse(High2, NumberStyles.HexNumber, CultureInfo.InvariantCulture);
            MapByte[3] = byte.Parse(High1, NumberStyles.HexNumber, CultureInfo.InvariantCulture);

            dataGridView_Map.Rows.Clear();
            for (int i = 0; i < 2; i++)
            {
                int Index = i * 2;
                int Value = (MapByte[Index + 1] * 256 + MapByte[Index]) - 32768;
                string[] RowsVal = new string[2];
                RowsVal[0] = (i * 5).ToString();
                RowsVal[1] = (Value).ToString();
                dataGridView_Map.Rows.Add(RowsVal);
            }
        }

        private void comboBox_ProgressMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            ProgressBarMode = byte.Parse(comboBox_ProgressMode.Text);
        }

        private void comboBox_ProgressSide_SelectedIndexChanged(object sender, EventArgs e)
        {
            ProgressBarLeft = GetProgressSide_Back();
        }

        private void comboBox_Page_SelectedIndexChanged(object sender, EventArgs e)
        {
            ScreenCurrentPage = byte.Parse(comboBox_Page.Text);
        }

        private void comboBox_StartupMenu_SelectedIndexChanged(object sender, EventArgs e)
        {
            ScreenCurrentMenu = GetMenu_Back();
        }

        private void button_SaveSettings_Click(object sender, EventArgs e)
        {
            SaveSettings();
        }

        private void button_Updates_Click(object sender, EventArgs e)
        {
            CheckConnectionToGithub();
        }

        private void dataGridView_Peaks_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                for (int i = 0; i < dataGridView_Peaks.Rows.Count; i++)
                {
                    if (!LockedPeaks(i))
                    {
                        PeaksMin[i] = int.Parse(dataGridView_Peaks.Rows[i].Cells[0].Value.ToString());
                        PeaksMax[i] = int.Parse(dataGridView_Peaks.Rows[i].Cells[0].Value.ToString());
                    }
                }
            }
            catch { }
        }

        void SelectEditing()
        {
            this.groupBoxMain.Visible = false;
            this.groupBoxPages.Visible = false;
            this.groupBoxO2Map.Visible = false;
            this.groupBoxDesc.Visible = false;
            this.groupBoxPeaks.Visible = false;

            if (comboBox_Editing.SelectedIndex == 0) this.groupBoxMain.Visible = true;
            if (comboBox_Editing.SelectedIndex == 1) this.groupBoxPages.Visible = true;
            if (comboBox_Editing.SelectedIndex == 2) this.groupBoxO2Map.Visible = true;
            if (comboBox_Editing.SelectedIndex == 3) this.groupBoxDesc.Visible = true;
            if (comboBox_Editing.SelectedIndex == 4) this.groupBoxPeaks.Visible = true;
        }

        private void comboBox_Editing_SelectedIndexChanged(object sender, EventArgs e)
        {
            SelectEditing();
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            //textBox_Location.Text
            string TesttPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) + "\\Arduino";

            if (!Directory.Exists(TesttPath))
            {
                DialogResult result1 = MessageBox.Show("The folder '" + TesttPath  + "' doesnt exist" + Environment.NewLine + "Do you want to create it?", "Error", MessageBoxButtons.YesNo);
                if (result1 == DialogResult.Yes) Directory.CreateDirectory(TesttPath);
            }
            TesttPath += "\\BMDatalogger";
            if (!Directory.Exists(TesttPath))
            {
                DialogResult result1 = MessageBox.Show("The folder '" + TesttPath + "' doesnt exist" + Environment.NewLine + "Do you want to create it?", "Error", MessageBoxButtons.YesNo);
                if (result1 == DialogResult.Yes) Directory.CreateDirectory(TesttPath);
            }

            if (Directory.Exists(TesttPath))
            {
                textBox_Location.Text = TesttPath;
                GitUpdate();

                DialogResult result1 = MessageBox.Show("Do you want to download and install the Arduino Software too?", "Error", MessageBoxButtons.YesNo);
                if (result1 == DialogResult.Yes) Process.Start("https://www.arduino.cc/en/main/software");
            }
        }

        private void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(1);
        }

        private void ComboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(3);
        }

        private void ComboBox5_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(5);
        }

        private void ComboBox7_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetPageIndex(7);
        }
    }
}
