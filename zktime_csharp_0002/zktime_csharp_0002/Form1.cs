using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ZKFPEngXControl;
using System.IO;
//using File;
namespace zktime_csharp_0002
{
    public partial class mainForm : Form
    {

        ZKFPEngX fp = null;
        int fpcHandle = 0;
        int MATCH_SCORE = 0;
        int PROCESS_NUM = 1;
        int FPID = 1; //first finger ID, should be increment
        //ZKFPEngXControl fpc = new ZKFPEngXControl();
        string templateFilePath = "D:\\RESEARCHS\\fingerprint\\downloaded";

        public mainForm()
        {
            InitializeComponent();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            btnDisconnect_Click(null,null);
        }

       


        private void fp_OnImageReceived(ref bool AImageValid)
        {
            debugRichText("fp_OnImageReceived");         
        }

        private void btConnect_Click(object sender, EventArgs e)
        {

            if (fp == null) fp = new ZKFPEngX();
            fp.SensorIndex = 0;
            var rValue = fp.InitEngine();

            
            if (rValue == 0)
            {
                fp.SensorIndex = 0;
                lblMessage.Text = "Sensor connected";
                //fp.OnCapture += new
                // IZKFPEngXEvents_OnCaptureEventHandler(fp_OnCapture_None);
                //fp.reg
                fp.OnCapture += new
                IZKFPEngXEvents_OnCaptureEventHandler(fp_OnCapture);

                //fp.OnImageReceived += new
                //IZKFPEngXEvents_OnImageReceivedEventHandler(fp_OnImageReceived);
                 
                
                btnDisconnect.Enabled = true;
                btConnect.Enabled = false;

                //fpcHandle = fp.CreateFPCacheDBEx();
                fpcHandle = fp.CreateFPCacheDB();
                if (fpcHandle <= 0)
                {
                    debugRichText("fpcHandle creation failed");
                }
                else
                {
                    debugRichText("fpcHandle creation success: "+fpcHandle);

                }


            }
            else if (rValue == 1)
                lblMessage.Text += " The loading of the fingerprint identification driver failed";
            else if (rValue == 2)
                lblMessage.Text += "Finger print Sensor has not been connected.";
            else if (rValue == 3)
                lblMessage.Text += "The fingerprint Reader appointed by the property SensorIndex dose not exist";
            else
                lblMessage.Text += "";



        }    

        

        

        /// <summary>
        /// Convert template object to bitmap.
        /// </summary>
        /// <param name="obj"></param>
        /// <ret
        /// 
        /// urns>Bitmap</returns>
        public Bitmap ObjectToBitmap(object templateObject)
        {
            if (templateObject != null)
            {
                var bimage = new Bitmap(new MemoryStream((byte[])templateObject));
                return bimage;
            }
            else
            {
                return null;
            }

        }

        /// <summary>
        /// To Capture and process template object into bitmap.
        /// </summary>
        /// <param name="ActionResult"></param>
        /// <param name="ATemplate"></param>
        private void fp_OnCapture_None(bool ActionResult, object ATemplate)
        {
            //Console.Out.WriteLine("fp_OnCapture_None");
            lblMessage.Text += "->fp_OnCapture_None";
        }
        static bool DBG_TPL = false;
        private void fp_OnCapture(bool ActionResult, object ATemplate)
        {

            debugRichText("fp_OnCapture");

            if (ActionResult) //if fingerprint is captured successfully
            {


                debugRichText("Q: "+fp.LastQuality);

                string cp_format = "yyyy_MM_dd_HH_mm_ss";
                string cp_pref = DateTime.Now.ToString(cp_format);

                lblMessage.Text += "->fpoc_ActionResult# ";
                //bool ARegFeatureChanged = true;
                string templates = fp.GetTemplateAsStringEx("9");
                string templates10 = fp.GetTemplateAsStringEx("10");

                if(DBG_TPL)
                lblMessage.Text += "->"+templates+"# ";  
                

                string path = templateFilePath + "\\fingerprint.tpl";
                




                //before save must exist before
                // if not woring .. just restart applications ...
                //File.WriteAllText(path, fp.GetTemplateAsStringEx("10.0"));
                lblMessage.Text += "->writing " + templates.Length + "...# ";
                File.WriteAllText(path, templates);
                //File.Open(path);
                
                //
                //lblMessage.Text += "->"+path +" written# ";
               
                /* string regTemplate = File.ReadAllText(templateFilePath + "fingerprint.tpl");
                string verTemplate = fp.GetTemplateAsString();
                */
                var response = fp.GetFingerImage(ref ATemplate);
                if (response)
                //if(true)
                {
                    lblMessage.Text += "->GFI true# ";
                    
                    //Bitmap bimage = new Bitmap(templateFilePath+"\\fingerprint.bmp", true);
                    //object img = bimage as object;
                    debugRichText( "saving bmp...");
                    Bitmap bimage = ObjectToBitmap(ATemplate);
                    if (bimage != null)
                    {
                        //before save must exist before
                        // if not woring .. just restart applications ...
                        fingerPrintBox.Image = bimage;
                        string jpgfn = templateFilePath + "\\test.jpg";
                        if (!File.Exists(jpgfn))
                        {
                            File.Create(jpgfn);
                        } 
                        bimage.Save(jpgfn);
                        string cp_jpgfn = templateFilePath + "\\" + cp_pref + ".jpg";
                        File.Copy(jpgfn, cp_jpgfn, true);
                        debugRichText( "saved");
                        if (radioV1N.Checked)
                        {
                            match1N(fpcHandle, ATemplate, ref MATCH_SCORE, ref PROCESS_NUM);
                        }
                        else if(radioRegister.Checked)
                        {

                            if (fp.LastQuality >= 50)
                            {
                                if (radioThumb.Checked) FPID = 1;
                                if (radioIndex.Checked) FPID = 2;
                                
                                registerFinger(fpcHandle, FPID, templates, templates10);
                            }
                        }



                    }
                    else
                    {
                        debugRichText( "Not Saved null");
                    
                    }
                    
                }
                else
                {
                    debugRichText( "GFI false");
                }

            
            }
            else
            {
                //failed to capture a valid fingerprint
                debugRichText( "failed to capture a valid fingerprint");
            }
        }

        void registerFinger(int fpcHandle, int fpid, string sRegTemplate, string sRegTemplate10)
        {

            debugRichText("registerFinger " + "," + fpcHandle + "," + fpid + "," + sRegTemplate.Length + "," );
            if (sRegTemplate10.Length > 0)
            {
                //var response = fp.AddRegTemplateStrToFPCacheDBEx(fpcHandle, fpid, sRegTemplate, sRegTemplate10);
                var response = fp.AddRegTemplateStrToFPCacheDB(fpcHandle, fpid, sRegTemplate);
                debugRichText("rF response: " + response);
            }
            else
                debugRichText("Register 10.0 failed, template length is zero");

        }

        void match1N(int fpcHandle, object ATemplate, ref int Score, ref int ProcessNum)
        {
            debugRichText("match1N");
            int id = -1;
            int f = 0;
            object A = null;
            int S = 8;
            int PN = 1;
            id = fp.IdentificationInFPCacheDB(fpcHandle, ATemplate, ref Score, ref ProcessNum);
            //var regsTemplatestr = ATemplate.ToString();
            id = fp.IdentificationFromStrInFPCacheDB(fpcHandle, ATemplate.ToString(), ref Score, ref ProcessNum);
            //id = fp.IdentificationInFPCacheDB(f, A, ref S, ref PN);
            if (id == -1)
            {
                debugRichText("Identify Failed");
            }
            else
            {
                debugRichText("Identify Succeed ID = "+id+" Score = "+Score
                    +"  Processed Number = "+ProcessNum);
                //SetDlgItemText(IDC_EDTHINT, buffer);
            }
        }

        void debugRichText(string msg)
        {
            lblMessage.Text += "->"+msg+"# ";
            lblMessage.ScrollToCaret();

        }
        /// <summary>
        /// Enrolling the fingerprint.
        /// </summary>
        /// <param name="ActionResult"></param>
        /// <param name="ATemplate"></param>
        private void fp_OnEnroll(bool ActionResult, object ATemplate)
        {
            debugRichText("fp_OnEnroll");
            /*if (ActionResult)
            {
                if (fp.LastQuality >= 80) //to ensure the fingerprint quality
                {
                    string regTemplate = fp.GetTemplateAsStringEx("10.0");
                    File.WriteAllText(templateFilePath + "\fingerprint.tpl", regTemplate);
                    fp.IsRegister = true;
                }
                else
                {
                    //Quality is too low
                }
            }
            else
            {
                //Register Failed
            }*/
        }

        /// <summary>
        /// To connect to sensor.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnConnectSensor_Click(object sender, EventArgs e)
        {
            // fp.SensorIndex = 0;
            var rValue = fp.InitEngine();

            if (rValue == 0)
            {
                fp.SensorIndex = 0;
                lblMessage.Text += "->Sensor connected\n";
                fp.OnCapture += new IZKFPEngXEvents_OnCaptureEventHandler(fp_OnCapture);
                //fp.OnImageReceived += new IZKFPEngXEvents_OnImageReceivedEventHandler(fp_OnImageReceived);

            }
            else if (rValue == 1)
                lblMessage.Text = " The loading of the fingerprint identification driver failed";
            else if (rValue == 2)
                lblMessage.Text = "Finger print Sensor has not been connected.";
            else if (rValue == 3)
                lblMessage.Text = "The fingerprint Reader appointed by the property SensorIndex dose not exist";
            else
                lblMessage.Text = "";


        }

        /// <summary>
        /// To disconnect from sensor.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDisconnect_Click(object sender, EventArgs e)
        {
            btConnect.Enabled = true;
            if (fp == null) 
                return; //already ..
            if (fpcHandle > 0)
            {
                fp.FreeFPCacheDBEx(fpcHandle);
            } 
            //fp.SensorIndex = 2;
            fp.EndEngine();
            
            //fp.OnCapture = null;
            fp = null;
            lblMessage.Text += "->Sensor disconnected.";
            btnDisconnect.Enabled = false;
        }


        IZKFPEngXEvents_OnEnrollEventHandler OE = null;
        /// <summary>
        /// To register the fingeprint.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /*private void btnRegister_Click(object sender, EventArgs e)
        {

            debugRichText("Registering ...");
            fp.BeginEnroll();
            if (OE == null)
            {
                OE=new IZKFPEngXEvents_OnEnrollEventHandler(fp_OnEnroll);
                fp.OnEnroll += OE;
            }
            //fp.OnImageReceived += new IZKFPEngXEvents_OnImageReceivedEventHandler(fp_OnImageReceived);
        }*/


/*        private void btnIdentify1N_Click(object sender, EventArgs e)


        {

            fp.CancelEnroll();
            bool ARegFeatureChanged = true;
            string regTemplate = File.ReadAllText(templateFilePath + "fingerprint.tpl");
            string verTemplate = fp.GetTemplateAsString();

            bool result = fp.VerFingerFromStr(ref regTemplate, verTemplate, true, ref ARegFeatureChanged);
            if (result)
            {
                //matched
                lblMessage.Text += "->Matched";
            }
            else
            {
                //not matched
           
     lblMessage.Text = "->Not Matched";
            }
        }*/

        

        private void btnBeep_Click(object sender, EventArgs e)
        {
            //fp.beep()
            fp.ControlSensor(13, 1);
            fp.ControlSensor(13, 0);
        }

        private void btGreen_Click(object sender, EventArgs e)
        {
            //fp.beep()
            fp.ControlSensor(11, 1);
            fp.ControlSensor(11, 0);

        }

        private void btRed_Click(object sender, EventArgs e)
        {
            fp.ControlSensor(12, 1);
            fp.ControlSensor(12, 0);

        }

        private void radioV1N_CheckedChanged(object sender, EventArgs e)
        {
            syncRadios();
        }


        private void syncRadios()
        {
            debugRichText("synchronize radios ...");
            if (radioV1N.Checked|radioV1_1.Checked)
            {
                if (fp.IsRegister)
                    fp.CancelEnroll();
                //no need to start capture
            }

            
            
            //
            if (radioRegister.Checked)
            {
                fp.CancelEnroll();
                fp.EnrollCount=3;
                fp.BeginEnroll();
                if (OE == null)
                {
                    OE = new IZKFPEngXEvents_OnEnrollEventHandler(fp_OnEnroll);
                    //@todo COMException 0x80040202 
                    fp.OnEnroll += OE;
                }

            }

            //debugRichText("Enroll count"+fp.);
            
        }

        private void btRegister_CheckedChanged(object sender, EventArgs e)
        {
            syncRadios();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            syncRadios();
        }
       

    }
}
