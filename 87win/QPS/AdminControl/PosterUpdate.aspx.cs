using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using QPS.DAL;

namespace QPS.Web.AdminControl
{
    public partial class PosterUpdate : DataHandler.BasePage
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


        public void BindShow()
        {
            DataSet dse = new DataSet();
            QPS.NEW.BLL.Poster pt = new QPS.NEW.BLL.Poster();
            dse = pt.GetList("  id =" + tempID + " ");
            this.txName.Text = dse.Tables[0].Rows[0]["Url"].ToString();
            this.Photo.Text = dse.Tables[0].Rows[0]["PhotoUrL"].ToString();

        }

        //修改
        protected void btnupdate_Click(object sender, EventArgs e)
        {
            string id = Request["ID"].ToString();

            string name = this.txName.Text; //链接地址
            string imagePath = this.Photo.Text;

            QPS.NEW.Model.Poster mpt = new QPS.NEW.Model.Poster();
            mpt.Id = Convert.ToInt32(id);
            mpt.URL = name;
            mpt.URL = imagePath;

            QPS.NEW.BLL.Poster pt =new QPS.NEW.BLL.Poster ();
            //rm.Add(Mro);
            if (pt.Update(mpt))
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
