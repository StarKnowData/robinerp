using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.AdminControl
{
    public partial class DocumentXQ : DataHandler.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                string ID = Convert.ToString(Request["id"]);
                Model.Document dc = new QPS.Model.Document();
                QPS.BLL.Document Bdc = new QPS.BLL.Document();
                dc = Bdc.GetModel(Convert.ToInt32(ID));
                this.txtTitle.Text = dc.DTity;
                this.Content.Text = dc.DContent;
            }
            
        }
        protected void bntQueding_Click(object sender, EventArgs e)
        {
            string id = Request["ID"].ToString();
            string title = this.txtTitle.Text;
            string con = this.Content.Text;
            Model.Document mdc = new QPS.Model.Document();
            mdc.Id = Convert.ToInt32(id);
            mdc.DTity = title;
            mdc.DContent = con;
            mdc.DTime = DateTime.Now.ToString();
            QPS.BLL.Document Bdc = new QPS.BLL.Document();
            if (Bdc.Update(mdc))
            {
                Response.Write("<script>alert('修改成功!!');window.location.href = 'DocumentInfro.aspx';</script>");
            }
            else
            {
                Response.Write("<script>alert('修改失败!!');</script>");
            }

        }


        
    }
}
