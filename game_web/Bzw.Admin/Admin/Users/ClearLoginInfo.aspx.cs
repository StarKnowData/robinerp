using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Bzw.Data;
using BCST.Common;

public partial class Admin_Users_ClearLoginInfo : AdminBasePage
{
	protected DataRow Info;

	/// <summary>
	/// 是否登录大厅
	/// </summary>
	protected string IsInZ = "否";
	/// <summary>
	/// 是否登录游戏
	/// </summary>
	protected string IsInW = "否";
	/// <summary>
	/// 游戏名称
	/// </summary>
	protected string GameName = "";
	/// <summary>
	/// 房间名称
	/// </summary>
	protected string RoomName = "";
	protected string ZID = "";
	protected string WID = "";
    
    protected void Page_Load(object sender, EventArgs e)
	{
		AdminPopedom.IsHoldModel( "04" );
        if (Request.QueryString["userid"] != null && Request.QueryString["userid"] != "")
        {
            Unlock(Request.QueryString["userid"]);
        }
        if (Request.QueryString["action"] != null && Request.QueryString["action"] == "unLockAll")
        {
            UnLockAll();
        }
        BindList();
     
    }
    //绑定所有的限制用户
    public void BindList()
    {
        //玩家类型
        string usertype = Utility.Common.GetStringOfUrl("usertype");
        //关键字
        string kw = Utility.Common.GetStringOfUrl("kw");
        string where = " and userid in  (select userid from TZLoginRecord UNION SELECT UserID FROM dbo.TWLoginRecord)";
        if (usertype == "robotplayer")
        {
            where += " and isrobot=1";
        }
        else if (usertype == "all")
        {

        }
        else
        {
            where += " and isrobot=0";
        }
        if (!string.IsNullOrEmpty(kw))
        { 
            string ktype=Utility.Common.GetStringOfUrl("ktype");
            where += " and " + ktype + " like '%" + kw + "%'";
        }
        
        DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
           .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
           .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
           .AddInputParameter("@Columns", DbType.String, "*")
           .AddInputParameter("@TableName", DbType.String, "Web_VUsersList")
           .AddInputParameter("@Wheres", DbType.String, where)
           .AddInputParameter("@KeyName", DbType.String, "UserID")
           .AddInputParameter("@OrderBy", DbType.String, " RegisterTM desc")
           .ToDataSet();
        if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
        {
            DataTable dt = ds.Tables[1];
            dt.Columns.Add("IsInZ", typeof(bool));
            dt.Columns.Add("IsInW", typeof(bool));
          
            foreach (DataRow row in dt.Rows)
            {
                
                row["IsInZ"] = DbSession.Default.FromSql("select count(userid) from TZLoginRecord where userid=" + row["UserID"]).ToScalar();
                row["IsInW"] = DbSession.Default.FromSql("select count(userid) from TWLoginRecord where userid=" + row["UserID"]).ToScalar();
               
            }
            
            anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
            anpPageIndex.CurrentPageIndex = PageIndex;

            UserList.DataSource = dt;
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

    //protected void btnSubmit_Click( object sender, EventArgs e )
    //{
    //    if( !CommonManager.Web.CheckPostSource() )
    //        return;
    //    if( !IsValid )
    //        return;

    //    phInfo.Visible = true;

    //    string sql = "select top 1 * from VUsers where UserName='" + txtUserName.Text.Trim() + "' or NickName ='" + txtUserName.Text.Trim() + "'";

    //    DataTable dt = DbSession.Default.FromSql( sql ).ToDataTable();
    //    if( dt.Rows.Count <= 0 )
    //        return;

    //    Info = dt.Rows[0];

    //    sql = "select * from TZLoginRecord where UserID=" + Info["UserID"].ToString();
    //    DataTable sdt = DbSession.Default.FromSql( sql ).ToDataTable();
    //    if( sdt.Rows.Count > 0 )
    //    {
    //        IsInZ = "是";
    //        ZID = sdt.Rows[0]["ZID"].ToString();
    //    }

    //    sdt.Clear();

    //    sql = "select * from TWLoginRecord where UserID=" + Info["UserID"].ToString();

    //    sdt = DbSession.Default.FromSql( sql ).ToDataTable();
    //    if( sdt.Rows.Count > 0 )
    //    {
    //        IsInW = "是";
    //        WID = sdt.Rows[0]["WID"].ToString();
    //        DataRow row = sdt.Rows[0];
    //        sql = "select a.RoomName,b.ComName from TGameRoomInfo as a inner join TGameNameInfo as b on a.GameNameID=b.NameID where a.RoomID=" + row["WID"].ToString();
    //        sdt.Clear();
    //        sdt = DbSession.Default.FromSql( sql ).ToDataTable();
    //        if( sdt.Rows.Count > 0 )
    //        {
    //            GameName = sdt.Rows[0]["ComName"].ToString();
    //            RoomName = sdt.Rows[0]["RoomName"].ToString();
    //        }
    //    }
    //}
    //解除某个用户的登录限制
	protected void Unlock(string userid)
	{
		DbSession.Default.FromSql( @"
			if exists (select UserID from TUsers where userid='" +userid+ @"')
			begin
			delete TZLoginRecord where UserID=(select UserID from TUsers where userid='" + userid + @"');
			delete TWLoginRecord where UserID=(select UserID from TUsers where userid='" + userid + @"');
			end
			" ).Execute();

		 CommonManager.Web.RegJs( this, "alert('操作成功！');location.href='clearLoginInfo.aspx';", false );
	}
    /// <summary>
    /// 解除所有用户的登录限制
    /// </summary>
    protected void UnLockAll()
    {
        DbSession.Default.FromSql("delete from  TZLoginRecord   delete from TWLoginRecord ").Execute();
        CommonManager.Web.RegJs(this, "alert('操作成功！');location.href='clearLoginInfo.aspx';", false);
    }
}
