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
        ZKFPEngX fp = new ZKFPEngX();
        string templateFilePath = "D:\\RESEARCHS\\fingerprint\\downloaded";

        public mainForm()
        {
            InitializeComponent();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            fp.EndEngine();
        }

       


        private void fp_OnImageReceived(ref bool AImageValid)
        {
         
         //var regTemplate = fp.GetTemplateAsString();
            lblMessage.Text += " ->on image received"; 
        }

        private void btConnect_Click(object sender, EventArgs e)
        {

            fp.SensorIndex = 0;
            var rValue = fp.InitEngine();

            if (rValue == 0)
            {
                fp.SensorIndex = 0;
                lblMessage.Text = "Sensor connected";
                    //fp.OnCapture += new
                     // IZKFPEngXEvents_OnCaptureEventHandler(fp_OnCapture_None);
                    fp.OnCapture += new
                    IZKFPEngXEvents_OnCaptureEventHandler(fp_OnCapture);
              //fp.OnImageReceived += new

                //IZKFPEngXEvents_OnImageReceivedEventHandler(fp_OnImageReceived);

            }
            else if (rValue == 1)
                lblMessage.Text += " The loading of the fingerprint identification driver failed";
            else if (rValue == 2)
                lblMessage.Text += "Finger print Sensor has not been connected.";
            else if (rValue == 3)
                lblMessage.Text += "The fingerprint Reader appointed by the property SensorIndex dose not exist";
            else
                lblMessage.Text += "";

            //fp.

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
        private void fp_OnCapture(bool ActionResult, object ATemplate)
        {

            lblMessage.Text += "->fp_OnCapture";

            if (ActionResult) //if fingerprint is captured successfully
            {


                lblMessage.Text += "->fpoc_ActionResult# ";
                bool ARegFeatureChanged = true;
                string templates = fp.GetTemplateAsString();
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
                    lblMessage.Text += "->saving bmp...# ";
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
                        lblMessage.Text += "->saved# ";
                        
                    }
                    else
                    {
                        lblMessage.Text += "->Not Saved null# ";
                    
                    }
                    
                }
                else
                {
                    lblMessage.Text += "->GFI false# ";
                }
                //var regsTemplatestr = ATemplate.ToString();

                /*Bitmap bimage = new Bitmap("D:\test\fingerprint.bmp", true);
                //object img = bimage as object;
                if (fp.GetFingerImage(ref ATemplate) && fp.SensorIndex == 0)
                {

                    lblMessage.Text+="->saving bmp...# ";
                    bimage = ObjectToBitmap(ATemplate);
                    bimage.Save(templateFilePath + "test.bmp");
                    fingerPrintBox.Image = bimage;
                    bimage.Save("D:\test\test.jpg");
                    lblMessage.Text += "-> jpg written# ";

                }*/
                /*
                bool result = fp.VerFingerFromStr(ref regTemplate, verTemplate, true, ref ARegFeatureChanged);
                if (result)
                {
                    //matched
                    lblMessage.Text += "->Matched# ";
                }
                else
                {
                    //not matched
                    lblMessage.Text += "->Not Matched# ";
                }*/
            }
            else
            {
                //failed to capture a valid fingerprint
                lblMessage.Text += "->failed to capture a valid fingerprint# ";
            }
        }

        /// <summary>
        /// Enrolling the fingerprint.
        /// </summary>
        /// <param name="ActionResult"></param>
        /// <param name="ATemplate"></param>
        private void fp_OnEnroll(bool ActionResult, object ATemplate)
        {
            lblMessage.Text += "->fp_OnEnroll";
            //fp.
            if (ActionResult)
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
            }
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
            fp.SensorIndex = 2;
            fp.EndEngine();
            lblMessage.Text += "->Sensor disconnected.";

        }

        /// <summary>
        /// To register the fingeprint.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnRegister_Click(object sender, EventArgs e)
        {

            fp.BeginEnroll();
            //fp.OnEnroll += new IZKFPEngXEvents_OnEnrollEventHandler(fp_OnEnroll);
            //fp.OnImageReceived += new IZKFPEngXEvents_OnImageReceivedEventHandler(fp_OnImageReceived);
        }


        private void btnIdentify1N_Click(object sender, EventArgs e)
        {
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
        }

       

    }
}
