using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using System.Data;
using QPS.DAL;

namespace QPS.Web.AdminControl
{
    public partial class ImagesUpdate : DataHandler.BasePage
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
        }

        void BindShow()
        {
            DataSet dse = new DataSet();
            QPS.BLL.Ad pt = new QPS.BLL.Ad();
            dse = pt.GetList("  id =" + tempID + " ");
            this.txtUrl.Text = dse.Tables[0].Rows[0]["adUrl"].ToString();
            this.Photo.Text = dse.Tables[0].Rows[0]["adImg"].ToString();
            this.txtName.Text = dse.Tables[0].Rows[0]["adName"].ToString(); 
        }


        //
        protected void btnupdate_Click(object sender, EventArgs e)
        {
            string id = Request["ID"].ToString();

            string name = this.txtUrl.Text; //链接地址
            string imagePath = this.Photo.Text;

            QPS.Model.ad a = new QPS.Model.ad();
            a.Id = Convert.ToInt32(id);
            a.AdUrl = name;
            a.AdImg = imagePath;

            QPS.BLL.Ad Ba = new QPS.BLL.Ad();
            //rm.Add(Mro);
            if (Ba.Update(a))
            {
                Response.Write("<script>alert('修改成功!!');</script>");
            }
            else
            {
                Response.Write("<script>alert('修改失败!!');</script>");
            }


        }

        protected void btnsure_Click(object sender, EventArgs e)
        {

        }

    }
}
