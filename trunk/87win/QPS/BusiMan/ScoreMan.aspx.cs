using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web.BusiMan
{
    public partial class ScoreMan : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            this.gdvScore.DataSource = Gettable();
            gdvScore.DataBind();
        } 
    
        public DataTable  Gettable()
        {   
            DataTable dt = new DataTable();
            QPS.NEW.BLL.Enterprise user = new QPS.NEW.BLL.Enterprise();
            QPS.NEW.BLL.Users u = new QPS.NEW.BLL.Users();
            QPS.NEW.Model.Room Mroom = new QPS.NEW.Model.Room();
            QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
            QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
            QPS.NEW.BLL.Integral Bint = new QPS.NEW.BLL.Integral();
            List<QPS.Model.Room> roomList = new List<QPS.Model.Room>();
            List<QPS.Model.Orderform> orderlist = new List<QPS.Model.Orderform>();
            //创建新列

            //DataColumn dc0 = dt.Columns.Add("积分编号", typeof(int));
            DataColumn dc1 = dt.Columns.Add("用户名称", typeof(string));
            //DataColumn dc2 = dt.Columns.Add("棋牌室名称", typeof(string));
            DataColumn dc3 = dt.Columns.Add("积分", typeof(string));
            //DataColumn dc4 = dt.Columns.Add("消费时间", typeof(string));
            if (Session["username"] != null)
            {
                //获取Uid
                string uname = Session["username"].ToString();
                DataSet dsUser = user.GetList("Username='" + uname + "'");
                int uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);



                QPS.NEW.Model.Integral mInt = new NEW.Model.Integral();
                mInt = Bint.GetModel(uid);
                if (mInt != null)
                {
                    DataRow dr = dt.NewRow();
                    dr[0] = uname;
                    dr[1] = mInt.TotalMoney.ToString();
                    dt.Rows.Add(dr);
                }

           }
                    return dt;
        }

        //protected void gdvRoom_RowDeleting(object sender, GridViewDeleteEventArgs e)
        //{
        //    //得到单位编号
  
        //    string rowToDelete = this.gdvScore.DataKeys[e.RowIndex].Values[0].ToString();
        //    int ID = Convert.ToInt32(rowToDelete);
        //    QPS.BLL.Integral Bint = new QPS.BLL.Integral();
        //    Bint.Delete(ID);
        //    this.gdvScore.DataSource = Gettable();
        //    gdvScore.DataBind();
        //}
    }
}

