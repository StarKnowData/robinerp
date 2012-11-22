using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using QPS.BLL;
using QPS.DAL;
using System.IO;

namespace QPS.Web.AdminControl
{
    public partial class RoomUpdate : DataHandler.BasePage
    {
        Dateshow class_data = new Dateshow();

        int tempID = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            
            if(!IsPostBack)
            {
                tempID = (Request["id"] != null) ? Convert.ToInt32(Request["id"]) : 0;
                BindShow();
            }

            if (Request.QueryString["type"] == "add")
            {
                btnsure.Visible = true;
            }
            else if (Request.QueryString["type"] == "LinkTo")
            {
                this.btnupdate.Visible = true;
                BindShow();
            }
        }

        public void BindShow()
        {
            DataSet dse = new DataSet();
            QPS.BLL.Room rm = new QPS.BLL.Room();
            dse = rm.GetList("  id =" + tempID + " ");

            this.txName.Text = dse.Tables[0].Rows[0]["Name"].ToString();
            this.ddlCat.SelectedValue = dse.Tables[0].Rows[0]["roomType"].ToString();
            this.Textprice.Text = dse.Tables[0].Rows[0]["roomPrice"].ToString();
            this.TextAre.Text = dse.Tables[0].Rows[0]["Are"].ToString();
            this.TextAddress.Text = dse.Tables[0].Rows[0]["Address"].ToString();
            //图片
            //this.upfile.Text = dse.Tables[0].Rows[0]["imagePath"].ToString();
            this.Photo.Text = dse.Tables[0].Rows[0]["imagePath"].ToString();
            this.Rec.Checked = Convert.ToInt32(dse.Tables[0].Rows[0]["IfRecommend"]) == 0 ? true : false;
            this.FileContent.Value = dse.Tables[0].Rows[0]["Content"].ToString();

        }

        //修改
        protected void btnupdate_Click(object sender, EventArgs e)
        {
           // string ID = this.RoomID.Text.ToString().Trim();
            string id = Request["ID"].ToString();

            string name	=this.txName.Text;        //棋牌室名称
            string type = this.ddlCat.SelectedValue.ToString();     //棋牌室类型

            //string type = this.ddlCat.Text;
            string Price =this.Textprice.Text;	  //棋牌室价格
            string are = this.TextAre.Text;         //棋牌室地域
            string address=this.TextAddress.Text;	     //祥细地址
            string imagePath =this.Photo.Text;	  //图片地址
            string content = this.FileContent.Value;	 //祥细介绍

            QPS.Model.Room Mro = new QPS.Model.Room();
            Mro.Id =Convert.ToInt32(id);
            Mro.Name = name;
            Mro.RoomType =type ;
            Mro.RoomPrice = Convert.ToDecimal(Price);
            Mro.Are = are;
            Mro.Address = address;
            Mro.ImagePath = imagePath;
            Mro.IfRecommend = this.Rec.Checked ? 0 : 1;
            Mro.Content = content;
            Mro.RecommendTime = DateTime.Now.ToString();

            QPS.BLL.Room rm = new QPS.BLL.Room();
            //rm.Add(Mro);
            if (rm.Update(Mro))
            {
                Response.Write("<script>alert('修改成功!!');</script>");
            }
            else
            {
                Response.Write("<script>alert('修改失败!!');</script>");
            }
        }

        //确定
        protected void btnsure_Click(object sender, EventArgs e)
        {
            //string name = this.txName.Text;        //棋牌室名称
            //string type = this.ddlCat.Text;     //棋牌室类型
            //string Price = this.Textprice.Text;	  //棋牌室价格
            //string are = this.Textprice.Text;         //棋牌室地域
            //string address = this.Textprice.Text;	     //祥细地址
            //string imagePath = this.Textprice.Text;	  //图片地址
            //string content = this.Textprice.Text;	 //祥细介绍

            //QPS.Model.Room Mro = new QPS.Model.Room();
            //Mro.Name = name;
            //Mro.RoomType = type;
            //Mro.RoomPrice = Price;
            //Mro.Are = are;
            //Mro.Address = address;
            //Mro.ImagePath = imagePath;
            //Mro.Content = content;
            //QPS.BLL.Room rm = new QPS.BLL.Room();
            //rm.Add(Mro);
            //int i = rm.Add(Mro);
            //if (i > 0)
            //{
            //    Response.Write("<script>alert('添加成功!!');</script>");
            //}
            //else
            //{
            //    Response.Write("<script>alert('添加失败!!');</script>");
            //}
        }

        //返回
        protected void btnback_Click(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// //图片路径上传
        /// </summary>
        /// <returns></returns>
        //private string getpicFileString()
        //{
        //    System.Web.HttpPostedFile hpFile = upfile.PostedFile;
        //    char[] chr = { '\\' };
        //    string[] str = hpFile.FileName.Split(chr);
        //    string filename1 = str[str.Length - 1];

        //    if (filename1 != "")
        //    {
        //        //jobfun.cs.function fun = new jobfun.cs.function();
        //        string savefilename = Server.MapPath("../upfile") + "/" + filename1;
        //        FileInfo f_name = new FileInfo(upfile.PostedFile.FileName);
        //        string s1 = f_name.Extension.ToString().ToLower();                  //取得后缀名
        //        filename1 = class_data.filename_random();
        //        if (s1 == ".jpg" || s1 == ".gif" || s1 == ".rar" || s1 == ".swf" || s1 == ".flv")
        //        {
        //            // 获得图片大小
        //            if (upfile.PostedFile.ContentLength < 4096000)
        //            {
        //                try
        //                {
        //                    string picweburl = Server.MapPath("../upfile") + "/" + filename1 + s1;//服务器路径
        //                    upfile.PostedFile.SaveAs(picweburl);

        //                    System.Drawing.Image srcImage = System.Drawing.Image.FromFile(picweburl);

        //                    class_data.SmallPic(picweburl, picweburl, srcImage.Width, srcImage.Height);

        //                    string saveSQLStr = "upfile/" + filename1 + s1;
        //                    //imgPicture.ImageUrl = uppicurl.Value;
        //                    return saveSQLStr;
        //                }
        //                catch (Exception ex)
        //                {
        //                    Response.Write("<script language=javascript>alert('" + ex.Message + "');</script>");
        //                    return null;
        //                }

        //            }
        //            else
        //            {
        //                Response.Write("<script language=javascript>alert('文件大小不能超过4096k');</script>");
        //                return null;
        //            }
        //        }
        //        else
        //        {
        //            Response.Write("<script language=javascript>alert('文件格式只能为jpg或gif或.swf');</script>");
        //            return null;
        //        }
        //    }
        //    else
        //        return null;

        //}



    }
}
