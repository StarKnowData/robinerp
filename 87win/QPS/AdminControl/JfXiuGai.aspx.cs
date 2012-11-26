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
    public partial class JFxg : System.Web.UI.Page
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
            QPS.NEW.BLL.Integral rm = new QPS.NEW.BLL.Integral();
            dse = rm.GetList("  UserID =" + tempID + " ");
            this.txtName.Text = dse.Tables[0].Rows[0]["UserID"].ToString();

            //this.txtTime.Text = dse.Tables[0].Rows[0]["CreateTime"].ToString();

            this.txtJiFen.Text = dse.Tables[0].Rows[0]["TotalMoney"].ToString();

            //this.txtRoom.Text = dse.Tables[0].Rows[0]["RoomId"].ToString();
        }

        protected void bntUpdate_Click(object sender, EventArgs e)
        {
            string id = Request["ID"].ToString();
            string jifen = this.txtJiFen.Text;

            QPS.NEW.Model.Integral Mro = new QPS.NEW.Model.Integral();
            //Mro.Id = Convert.ToInt32(id);
            //Mro.Content = Convert.ToInt32(jifen);
            Mro.UserID = Convert.ToInt32(id);
            Mro.TotalMoney = Convert.ToInt32(jifen);

            QPS.NEW.BLL.Integral rm = new QPS.NEW.BLL.Integral();
            int i =Convert.ToInt32( rm.UpdateContent(Mro));
            if (i >= -1)
            {
                Response.Write("<script>alert('修改成功!!');window.location.href = 'Jfgl.aspx';</script>");
            }
            else
            {
                Response.Write("<script>alert('修改失败!!');</script>");
            }
        }

    }
}
