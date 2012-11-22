namespace SdCms.Web.Admin
{
    using System;
    using System.IO;
    using System.Text;
    using System.Web.UI.HtmlControls;
    using System.Web.UI.WebControls;
    using System.Collections.Generic;
    //using SdCms.FrameWork;
    //using SdCms.FrameWork.Util;
    //using SdCms.Web.Admin.UI;

    public partial class Upload : DataHandler.BasePage
    {
        protected string rid = "Photo";

        protected void Button1_Click(object sender, EventArgs e)
        {
            if (!this.FileUpload1.HasFile)
            {
                this.Label1.Text = "没有选择要上传的文件！";
            }
            else
            {
                bool flag = false;
                string str = Path.GetExtension(this.FileUpload1.FileName).Substring(1);
                string[] strArray = {"jpg","jpeg","png","gif","swf"};
                for (int i = 0; i < strArray.Length; i++)
                {
                    if (strArray[i] == str)
                    {
                        flag = true;
                        str = "." + strArray[i];
                        break;
                    }
                }
                if (flag)
                {
                    string str3 = @"\";
                    string path = base.Server.MapPath("/upload") + str3;
                    MakeFolder(path);
                    string shortDateString = GetShortDateString();
                    string str6 = path + str3 + shortDateString + str3;
                    MakeFolder(str6);
                    string str8 = GetTimeNumString() + str;
                    string filename = str6 + str8;
                    string str10 = "/upload/" + shortDateString + "/" + str8;
                    try
                    {
                        this.FileUpload1.SaveAs(filename);
                        int contentLength = this.FileUpload1.PostedFile.ContentLength;
                        StringBuilder builder = new StringBuilder();
                        builder.Append("<script language=\"javascript\">");
                        builder.Append("window.opener.document.getElementById('" + this.rid + "').value='" + str10 + "';");  
                        builder.Append("window.close();");
                        builder.Append("</script>");
                        this.Page.ClientScript.RegisterClientScriptBlock(base.GetType(), "upload_ok", builder.ToString());
                    }
                    catch (Exception exception)
                    {
                        this.Label1.Text = "发生错误：" + exception.Message.ToString();
                    }
                }
                else
                {
                    this.Label1.Text = "请选择正确的文件类型！";
                }
            }
        }

        public void MakeFolder(string path)
        {
            DirectoryInfo info = new DirectoryInfo(path);
            if (!info.Exists)
            {
                info.Create();
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            
            if (!string.IsNullOrEmpty(base.Request.QueryString["rid"]))
            {
                this.rid = base.Request.QueryString["rid"];
            }

        }


        public string GetShortDateString()
        {
            return DateFormat("{0:yyyy-MM-dd}");
        }

        public string DateFormat(string pattern)
        {
            DateTime now = DateTime.Now;
            return string.Format(pattern, now);
        }

        public string GetTimeNumString()
        {
            DateTime now = DateTime.Now;
            StringBuilder builder = new StringBuilder();
            builder.Append(now.Hour);
            builder.Append(now.Minute);
            builder.Append(now.Second);
            builder.Append(now.Millisecond);
            return builder.ToString();
        }



    }





}

