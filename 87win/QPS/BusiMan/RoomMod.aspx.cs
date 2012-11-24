using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.BusiMan
{
    public partial class RoomMod : System.Web.UI.Page
    {   
        
        private int  roomid;
        private int ownerid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Session["username"] != null)
                {
                    roomid = Convert.ToInt32(Request.QueryString["roomid"]);
                    QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
                    QPS.NEW.Model.Room Mroom = Broom.GetModel(roomid);
                    ownerid = Mroom.OwnerID;
                    txfAddress.Value = Mroom.Address;
                    txfArea.Value = Mroom.Are;
                    txfContent.Value = Mroom.Content;
                    txfName.Value = Mroom.Name;
                    txfRoomPrice.Value = Mroom.RoomPrice.ToString();
                    txfRoomType.Value = Mroom.RoomState.ToString();
                }
            }
        }

        protected void btnCreate_Click(object sender, EventArgs e)
        {
            try
            {
                QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
                QPS.NEW.Model.Room Mroom = Broom.GetModel(roomid);
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
                Mroom.OwnerID = ownerid;
                Mroom.Address = txfAddress.Value;
                Mroom.Are = txfArea.Value;
                Mroom.Content = txfContent.Value.Length > 100 ? txfContent.Value.Substring(0,100) : txfContent.Value;
                Mroom.Name = txfName.Value;
                Mroom.RoomPrice = Convert.ToDecimal(txfRoomPrice.Value);
                Mroom.RoomState = Convert.ToInt32(txfRoomType.Value);
                Mroom.ImagePath = Upload(fulImg);
                Broom.Update(Mroom);
                Response.Write("<script>alert('修改棋牌室成功！')</script>");
                Response.Write("<script>window.close()</script>");
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert('修改棋牌室失败！')</script>");
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
