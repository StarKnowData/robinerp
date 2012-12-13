using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.AdminControl
{
    public partial class LeaveWordXq : DataHandler.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
                string ID =Convert.ToString(Request["id"]);
                NEW.Model.Leaveword m_leaveword = new QPS.NEW.Model.Leaveword();
                QPS.NEW.BLL.Leaveword lw = new QPS.NEW.BLL.Leaveword();
                m_leaveword = lw.GetModel(Convert.ToInt32(ID));
                this.txtTitle.Text = m_leaveword.title;
                this.Content.Text = m_leaveword.Content;
            }
            

        }

        protected void Button1_Click(object sender, EventArgs e)
        {

        }



        


    }
}
