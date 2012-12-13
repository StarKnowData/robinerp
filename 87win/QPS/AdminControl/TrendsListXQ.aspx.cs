using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.AdminControl
{
    public partial class TrendsListXQ : DataHandler.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
                string ID = Convert.ToString(Request["id"]);
                NEW.Model.Trends ts = new QPS.NEW.Model.Trends();
                QPS.NEW.BLL.Trends Bts = new QPS.NEW.BLL.Trends();
                ts = Bts.GetModel(Convert.ToInt32(ID));
                this.txtTitle.Text =ts.Title;
                this.Content.Text=ts.Content;
             }

        }

        //修改
        protected void bntUpdate_Click(object sender, EventArgs e)
        {
            string id = Request["ID"].ToString();
            string title = this.txtTitle.Text;
            string con = this.Content.Text;
            NEW.Model.Trends Mts = new QPS.NEW.Model.Trends();
            Mts.Id = Convert.ToInt32(id);
            Mts.Title=title;
            Mts.Content = con;
            Mts.Time = DateTime.Now.ToString();
            QPS.NEW.BLL.Trends Bts = new QPS.NEW.BLL.Trends();

            if (Bts.Update(Mts))
            {
                Response.Write("<script>alert('修改成功!!');window.location.href = 'TrendsList.aspx';</script>");
            }
            else
            {
                Response.Write("<script>alert('修改失败!!');</script>");
            }

        
        }

    }
}
