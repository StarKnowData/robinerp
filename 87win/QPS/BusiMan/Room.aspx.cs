using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web.BusiMan
{
    public partial class Room : System.Web.UI.Page
    {
        public DataSet ds;
        QPS.NEW.BLL.Enterprise user = new QPS.NEW.BLL.Enterprise();
        QPS.NEW.Model.Enterprise Muser = new QPS.NEW.Model.Enterprise();
        static int userid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Session["username"] != null)
                {
                    string uname = Session["username"].ToString();
                    DataSet dsUser = user.GetList("Username='" + uname + "'");
                    userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                }
            }
        }

        protected void btnCreate_Click(object sender, EventArgs e)
        {
            try
            {
                QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
                QPS.NEW.Model.Room Mroom = new QPS.NEW.Model.Room();
                if (this.fulImg.FileName == "")
                {
                    //this.lblMessage.Text = "<font color=#FF0000>请选择上传的图片!</font>";
                    this.fulImg.Focus();
                    return;
                }
                if (txfName.Value == string.Empty)
                {
                    Response.Write("<script>alert('用户名不能为空，请重新输入')</script>");
                    return;
                }
                if (txfRoomPrice.Value == string.Empty)
                {
                    Response.Write("<script>alert('请重新输入房间价格')</script>");
                    return;
                }
                if (txfAddress.Value == string.Empty)
                {
                    Response.Write("<script>alert('地址不能为空，请重新输入')</script>");
                    return;
                }
                if (txfArea.Value == string.Empty)
                {
                    Response.Write("<script>alert('地区不能为空，请重新输入')</script>");
                    return;
                }
                if (txfContent.Value == string.Empty)
                {
                    Response.Write("<script>alert('内容不能为空，请重新输入')</script>");
                    return;
                }
                if (txfRoomType.Value == string.Empty)
                {
                    Response.Write("<script>alert('房间类型不能为空，请重新输入')</script>");
                    return;
                }
                Mroom.Name = txfName.Value;
                Mroom.RoomPrice = Convert.ToDecimal(txfRoomPrice.Value);
                Mroom.RoomState = 0;
                Mroom.IfRecommend =1;
                Mroom.Address = txfAddress.Value;
                Mroom.Are = txfArea.Value;
                Mroom.Content = txfContent.Value.Length > 100 ? txfContent.Value.Substring(0, 100) : txfContent.Value;
                Mroom.RoomType = txfRoomType.Value;
                Mroom.OwnerID = userid;
                Mroom.ImagePath = Upload(fulImg);
                Mroom.Examine = 0;
                Broom.Add(Mroom);
                Response.Write("<script>alert('添加棋牌室成功！')</script>");
                Response.Write("<script>window.close()</script>");
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert('添加棋牌室失败！')</script>");
                return;
            }
        }
        public static string Upload(FileUpload fileupload)
        {
            //上传文件  
            string localpath;
            string nam = fileupload.PostedFile.FileName;
            int i = nam.LastIndexOf(".");
            string extension = nam.Substring(i);
            string fileName = DateTime.Now.ToString("yyyyMMddhhmmss");
            string path = System.Web.HttpContext.Current.Server.MapPath("../") + "upload/" + fileName + extension;
            fileupload.PostedFile.SaveAs(path);
            localpath = "upload/" + fileName + extension;
            return localpath;
        }
    }
}
