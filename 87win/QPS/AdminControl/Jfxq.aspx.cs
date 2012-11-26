using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

namespace QPS.Web.AdminControl
{
    public partial class Jfxq : DataHandler.BasePage
    {
        DataSet ds = new DataSet();

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                //string tempUserID =Convert.ToString(Request["userid"]);
                //QPS.BLL.Integral Ig = new QPS.BLL.Integral();
                //ds = Ig.SelectByJfxq(" where userid=" + tempUserID + "");
                //dgExamProj.DataSource = ds;
                //dgExamProj.DataBind();
                Bind();
            }
        }

        public void Bind()
        {
            string tempUserID = Convert.ToString(Request["userid"]);
            QPS.NEW.BLL.Integral Ig = new QPS.NEW.BLL.Integral();
            //ds = Ig.SelectByJfxq(" where userid=" + tempUserID + "");
            ds = Ig.SelectByJfxq(tempUserID);
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();
        }

        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            if (e.CommandName == "Update")
            {
                //Label lab = ((Label)e.Item.FindControl("lblPack"));
                Response.Redirect("JfXiuGai.aspx?id=" + e.CommandArgument.ToString());
            }

            if (e.CommandName == "delete")
            {
                string id = e.CommandArgument.ToString();
                
                QPS.NEW.BLL.Integral Binte = new QPS.NEW.BLL.Integral();
                try
                {
                    Binte.DeleteByUid(Convert.ToInt32(id));
                    Bind();
                    //Response.Redirect("Jfgl.aspx?id=" + e.CommandArgument.ToString());
                }
                catch (Exception ex)
                { }
            }
           
        }

        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }


        public string GetName(string tempStr)
        {
            string str = string.Empty;
            if (string.IsNullOrEmpty(tempStr))
                str = "棋牌室已不存在";
            else
                str = tempStr;
            return str;
        }



    }
}
