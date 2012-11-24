using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;
namespace QPS.Web.UserMan
{
    public partial class OrderMan : System.Web.UI.Page
    {
        public DataTable Gettable(List<QPS.NEW.Model.Room> roomlist)
        {
            try
            {
                //创建DataTable
                DataTable dt = new DataTable();
                //创建新列
                DataColumn dc0 = dt.Columns.Add("棋牌室编号", typeof(int));
                DataColumn dc1 = dt.Columns.Add("棋牌室名称", typeof(string));
                DataColumn dc2 = dt.Columns.Add("棋牌室类型", typeof(string));
                DataColumn dc3 = dt.Columns.Add("价格", typeof(string));
                DataColumn dc4 = dt.Columns.Add("地区", typeof(string));
                DataColumn dc5 = dt.Columns.Add("地址", typeof(string));
                //DataColumn dc6 = dt.Columns.Add("退订", typeof(Button));
                foreach (QPS.NEW.Model.Room r in roomlist)
                {
                    DataRow dr = dt.NewRow();
                    dr[0] = r.Id;
                    dr[1] = r.Name;
                    dr[2] = r.RoomType;
                    dr[3] = r.RoomPrice;
                    dr[4] = r.Are;
                    dr[5] = r.Address;
                    //dr[6] = ht[i]["B_AuthorName"];

                    dt.Rows.Add(dr);
                }
                return dt;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public void databind(GridView  gdv)
        {
            QPS.NEW.BLL.Users user = new QPS.NEW.BLL.Users();
            QPS.NEW.Model.Room Mroom = new QPS.NEW.Model.Room();
            QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
            QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
            List<QPS.NEW.Model.Room> roomList = new List<QPS.NEW.Model.Room>();
            if (Session["username"] != null)
            {
                string uname = Session["username"].ToString();
                DataSet dsUser = user.GetList("Username='" + uname + "'");
                int uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                List<QPS.NEW.Model.Orderform> orderlist = Border.GetModelList("Userid='" + uid + "'");
                foreach (QPS.NEW.Model.Orderform o in orderlist)
                {
                    int roomid = (int)o.Roomid;
                    roomList.Add(Broom.GetModel(roomid));
                }
            }
            gdv.DataSource = Gettable(roomList);
            gdv.DataBind();
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                databind(this.gdvPersonnalOrder);
            }
        }
        protected void gdvPersonnalOrder_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
           //得到单位编号
            string rowToDelete = gdvPersonnalOrder.DataKeys[e.RowIndex].Values[0].ToString();
          //转换为整数
           int ID=Convert.ToInt32(rowToDelete);
           QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
           QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
  
           DataSet dsorder= Border.GetList("Roomid ='" + ID + "'");
           int Oid = Convert.ToInt32(dsorder.Tables[0].Rows[0]["Id"]);
           Border.Delete(Oid);
           QPS.NEW.Model.Room r = Broom.GetModel(ID);
           r.RoomState = 0;
           Broom.Update(r);
           databind(gdvPersonnalOrder);
        }
    }
}
