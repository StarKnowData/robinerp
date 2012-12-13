using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
//using System.Xml.Linq;
//using SdCms.FrameWork.Db;
//using SdCms.FrameWork;
using System.IO;
using System.Text;

namespace SdCms.Web.Admin
{
    public partial class UpPhoto : DataHandler.BasePage
    {
        //public string photo;
        protected string pmtf = "jpg|png|gif|bmp";
        protected string rid = "Photo";


        protected void Button1_Click(object sender, EventArgs e)
        {
            string userName = Request["userId"].ToString();
            if (string.IsNullOrEmpty(userName))
            {
                Server.Transfer("Detail_Teacher.aspx");
            }
            else
            {
                if (!this.FileUpload1.HasFile)
                {
                    this.Label1.Text = "没有选择要上传的文件！";
                }
                else
                {
                    bool flag = false;
                    string str = Path.GetExtension(this.FileUpload1.FileName).Substring(1);
                    string[] strArray = this.pmtf.Split(new char[] { '|' });
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
                        string str2 = @"\";
                        string path = base.Server.MapPath(@"/UploadFile") + str2;

                        DirectoryInfo info = new DirectoryInfo(path);
                        if (!info.Exists)
                        {
                            info.Create();
                        }

                        DateTime now = DateTime.Now;
                        string shortDateString = now.ToString("yyyyMMddhhmmss");
                        string str5 = path + str2 + shortDateString + str2;
                        DirectoryInfo filePath = new DirectoryInfo(str5);
                        if (!filePath.Exists)
                            filePath.Create();

                        StringBuilder builder = new StringBuilder();
                        builder.Append(now.Hour);
                        builder.Append(now.Minute);
                        builder.Append(now.Second);
                        builder.Append(now.Millisecond);
                        string str7 = builder.ToString() + str;
                        string filename = str5 + str7;
                        //string photo = ObjectFactory.Instance.GetMemberDao.Get(userName).GetFieldValue("UserSpaceHomeDir").ToString().Trim() + Chinese2Spell.ConvertWithBlank(userName).Trim() + str;
                        //LogUtil.Info(photo);
                        try
                        {
                            this.FileUpload1.SaveAs(filename);
                            int contentLength = this.FileUpload1.PostedFile.ContentLength;
                            StringBuilder builderstr = new StringBuilder();
                            builderstr.Append("<script language=\"javascript\">");
                            builderstr.Append("window.opener.document.getElementById('" + this.rid + "').value='" + filename + "';");
                            builderstr.Append("window.close();");
                            builderstr.Append("</script>");
                            this.Page.ClientScript.RegisterClientScriptBlock(base.GetType(), "upload_ok", builder.ToString());
                        }
                        catch (Exception exception)
                        {
                            this.Label1.Text = "发生错误：" + exception.Message.ToString();
                        }
                    }
                    else
                    {
                        this.Label1.Text = "请选择正确的文件类型！[" + this.pmtf + "]";

                    }
                }
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            //DataField personal = null;  
            //personal = ObjectFactory.Instance.GetMemberDao.GetEnterprise(Request["userId"].ToString());

            //string userName = Request["userId"].ToString();
            //System.Data.DataTable dt = ObjectFactory.Instance.GetFileOprDao.GetUserPhoto(Convert.ToInt32(ObjectFactory.Instance.GetMemberDao.Get(userName).GetFieldValue("id")), Chinese2Spell.ConvertWithBlank(userName).Trim());
            //if (dt.Rows.Count > 0)
            //{
            //    this.img.ImageUrl = dt.Rows[0]["filehref"].ToString();
            //    //this.photo = dt.Rows[0]["filehref"].ToString();
            //}
        }
    }
}
