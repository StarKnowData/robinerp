using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.AdminControl
{
    public partial class RoomInsert : DataHandler.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
            
            }
        }


        //确定
        protected void btnsure_Click(object sender, EventArgs e)
        {
            string name = this.txName.Text;  //棋牌室名称
            string type = this.ddlCat.Text; //棋牌室类型
            string Price = this.Textprice.Text;	//棋牌室价格
            string are = this.Textprice.Text; //棋牌室地域
            string address = this.Textprice.Text; //祥细地址
            string imagePath = this.Textprice.Text;	//图片地址
            string content = this.Textprice.Text;//祥细介绍
            string IfR = "";
            if(this.Rec.Checked)
            {
                IfR = "0";
            }
            QPS.NEW.Model.Room Mro = new QPS.NEW.Model.Room();
            Mro.Name = name;
            Mro.RoomType = type;
            Mro.RoomPrice = Convert.ToDecimal(Price);
            Mro.Are = are;
            Mro.Address = address;
            Mro.ImagePath = imagePath;
            Mro.Content = content;
            Mro.IfRecommend =Convert.ToInt32(IfR);

            QPS.NEW.BLL.Room rm = new QPS.NEW.BLL.Room();
            //rm.Add(Mro);
            int i = rm.Add(Mro);
            if (i > 0)
            {
                Response.Write("<script>alert('添加成功!!');</script>");
            }
            else
            {
                Response.Write("<script>alert('添加失败!!');</script>");
            }

        }


        //返回
        protected void btnback_Click(object sender, EventArgs e)
        {

        }

        protected void btnupdate_Click(object sender, EventArgs e)
        {

        }

        
    }
}
