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
    public partial class JfIndert : System.Web.UI.Page
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
            QPS.BLL.Users Bus = new QPS.BLL.Users();
            dse = Bus.GetList("  id =" + tempID + " ");

            this.txtId.Text = tempID.ToString();
            this.txtName.Text = dse.Tables[0].Rows[0]["Username"].ToString();
            this.txtPhone.Text = dse.Tables[0].Rows[0]["Phone"].ToString();

        }

        //添加
        protected void Button1_Click(object sender, EventArgs e)
        {
            string uid = this.txtId.Text;
            string uname = this.txtName.Text;
            string jf = this.txtJf.Text;

            QPS.Model.Integral Mgral = new QPS.Model.Integral();
            Mgral.UserID = uid;
            Mgral.Content = Convert.ToInt32(jf);
            Mgral.CreateTime = DateTime.Now;

            QPS.BLL.Integral Bin =new QPS.BLL.Integral ();
            int i=Bin.Add(Mgral);
            if (i >= 0)
            {
                Response.Write("<script>alert('积分添加成功!!');window.location.href = 'UserInfo.aspx';</script>");
            }
            else
            {
                Response.Write("<script>alert('积分添加失败!!');</script>");
            }

        }
    }
}
