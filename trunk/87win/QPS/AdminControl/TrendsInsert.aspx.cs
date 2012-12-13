using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.AdminControl
{
    public partial class TrendsInsert : DataHandler.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        //添加
        protected void bntInsert_Click(object sender, EventArgs e)
        {
            
            string title = this.txtTitle.Text;
            string con = this.Content.Text;
            NEW.Model.Trends Mts = new QPS.NEW.Model.Trends();
           
            Mts.Title = title;
            Mts.Content = con;
            Mts.Time = DateTime.Now.ToString();
            QPS.NEW.BLL.Trends Bts = new QPS.NEW.BLL.Trends();

            int i = Bts.Add(Mts);

            if (i > 0)
            {
                Response.Write("<script>alert('添加成功!!');window.location.href = 'TrendsList.aspx';</script>");
            }
            else
            {
                Response.Write("<script>alert('添加失败!!');</script>");
            }
        }
    }
}
