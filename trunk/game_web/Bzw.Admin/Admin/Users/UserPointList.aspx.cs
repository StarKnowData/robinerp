using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using System.Text;
using BCST.Common;
using Utility;

 
    public partial class Admin_Users_UserPointList :  AdminBasePage
    {
        public string GameList;
        protected void Page_Load(object sender, EventArgs e)
        {
            BindGameList();
            DelUserPoint();
            if (!IsPostBack)
            {
                BindPointList();
            }
        }
        //删除用户积分
        protected void DelUserPoint()
        {
            string action = Utility.Common.GetStringOfUrl("act");
            if(!string.IsNullOrEmpty(action))
            {
                if (action == "del")
                { 
                    //删除用户积分
                    string userid = Utility.Common.GetStringOfUrl("uid");
                    string nameid = Utility.Common.GetStringOfUrl("nameid");
                    int i = DbSession.Default.FromSql("delete from TmatchTable where userid=@UserID and NameID=@NameID ").AddInputParameter("@UserID", DbType.Int32, userid)
                                            .AddInputParameter("@NameID", DbType.Int32, nameid).Execute();
                    if (i > 0)
                    {
                        //管理员操作日志
                        string descript = "删除游戏用户的积分，用户ID为" + userid + "，游戏id为"+nameid;
                        string system = Common.GetOS;
                        new BLL.Member().InsertAdminModifyLog(AdminInfo["UserName"].ToString(), Common.RequestIP, system, descript, 1);
                        Response.Write("<script>alert('温馨提示：\\n\\n删除积分操作成功！');location.href='" + Server.UrlDecode(Utility.Common.GetStringOfUrl("url")) + "';</script>");
                    }
                }
            }

        }
        //绑定游戏列表
        protected void BindGameList()
        {
            GameList = "<option value='' selected='selected'>请选择</option>";
            DataTable dt = DbSession.Default.FromSql(" SELECT * FROM dbo.TGameNameInfo WHERE NameID IN (SELECT NameID FROM dbo.TGameRoomInfo WHERE GameTypeID=1)").ToDataTable();
            if (dt.Rows.Count > 0)
            {
                foreach (DataRow row in dt.Rows)
                {
                    GameList = GameList + "<option value='" + row["NameID"].ToString() + "'>" + row["ComName"].ToString() + "</option>";
                }

            }
        }
        //绑定玩家积分列表
        protected void BindPointList()
        {
            StringBuilder where = new StringBuilder();
            string order = CommonManager.Web.RequestUrlDecode("sorttype", "");
            string searchType = CommonManager.Web.RequestUrlDecode("sttype", "");
            string userType = CommonManager.Web.RequestUrlDecode("usertype", "");
            string gameNameId = CommonManager.Web.RequestUrlDecode("nameid", "");
            string key = CommonManager.Web.RequestUrlDecode("key", "");

            //排序
            if (string.IsNullOrEmpty(order))
            {
                order = " Point desc";
            }
            else
            {
                order = " Point " + order;
            }
            //关键字搜索
            if (!string.IsNullOrEmpty(key))
            {
                if (!string.IsNullOrEmpty(searchType))
                { 
                    where.Append( (searchType=="byid")?" and UserID like '%"+key+"%'":" and UserName like '%"+key+"%'");
                }
            }
            //通过游戏搜索
            if (!string.IsNullOrEmpty(gameNameId))
            {
                where.Append(" and NameID="+gameNameId);
            }
            //搜索用户类型 默认为真实玩家
            if (!string.IsNullOrEmpty(userType))
            {
                where.Append((userType == "realplayer") ? " and userid in (select userid from tusers where isrobot=0)" : (userType == "robotplayer") ? " and userid in (select userid from tusers where isrobot=1)" : "");

            }
            else
            {
                where.Append(" and userid in (select userid from tusers where isrobot=0) ");
            }
           
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
           .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
           .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
           .AddInputParameter("@Columns", DbType.String, "*")
           .AddInputParameter("@TableName", DbType.String, "Web_vUserPoint")
           .AddInputParameter("@Wheres", DbType.String,  where.ToString())
           .AddInputParameter("@KeyName", DbType.String, "UserID")
           .AddInputParameter("@OrderBy", DbType.String, order)
           .ToDataSet();
            if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                UserList.DataSource = ds.Tables[1];
                UserList.DataBind();
                UserList.Visible = true;
                NoUserList.Visible = false;
            }
            else
            {
                this.NoUserList.Visible = true;
                UserList.Visible = false;
            }
        }
    }
 
