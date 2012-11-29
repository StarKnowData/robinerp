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

public partial class Admin_Games_GameRooms : AdminBasePage
{
    public string RoomBigID;
    string RoomSmallID;
    string sqlwhere;
    string SqlW, SqlC;
    public int tableids;
    string para = "";
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

        DataTable sdBig = new DataTable();
        string sqlBig = "select * from TGameKindInfo order by IDSort desc";
		sdBig = DbSession.Default.FromSql( sqlBig ).ToDataTable(); //sqlconn.sqlReader(sqlBig);
        if (sdBig.Rows.Count > 0)
        {
			GameBigList.DataSource = sdBig;
			GameBigList.DataBind();
        }
        else
        {
            this.NoGameBigList.Visible = true;
        }
        sdBig.Clear();

		RoomBigID = CommonManager.Web.Request( "bid", "" );//Limit.getFormValue("bid");

        if (RoomBigID.ToString() == "")
        {
            sqlwhere = " order by IDSort DESC";
        }
        else
            sqlwhere = "where KindID=" + RoomBigID + " order by IDSort DESC";

        DataTable sdSmall = new DataTable();
        string sqlSmall = "select NameID,ComName from TGameNameInfo " + sqlwhere + "";
		sdSmall = DbSession.Default.FromSql( sqlSmall ).ToDataTable(); //sqlconn.sqlReader(sqlSmall);
        if (sdSmall.Rows.Count > 0)
        {
			GameSmallList.DataSource = sdSmall;
			GameSmallList.DataBind();
        }
        else
        {
            this.NoGameSmallList.Visible = true;
        }
        sdSmall.Clear();

        if (!IsPostBack)
        {
            RoomListInfo();
        }
    }


    protected void RoomListInfo()
    {
		RoomSmallID = CommonManager.Web.Request( "sid", "" );//Limit.getFormValue("sid");

        if (RoomBigID.ToString() == "" && RoomSmallID.ToString() == "")
        {
            SqlW = "";
            SqlC = "";
            //para = "";
        }
        else if (RoomBigID.ToString() != "" && RoomSmallID.ToString() == "")
        {
            SqlW = " and GamekindID='" + RoomBigID + "'";
			SqlC = " and GamekindID='" + RoomBigID + "'";
            para = "bid=" + RoomBigID;
        }
        else if (RoomBigID.ToString() != "" && RoomSmallID.ToString() != "")
        {
			SqlW = " and GamekindID='" + RoomBigID + "' and GameNameid='" + RoomSmallID + "'";
			SqlC = " and GamekindID='" + RoomBigID + "' and GameNameid='" + RoomSmallID + "'";
            para = "bid=" + RoomBigID + "&sid=" + RoomSmallID;
        }
		else if( RoomSmallID.ToString() != "" )
		{
			SqlW = " and  GameNameid='" + RoomSmallID + "'";
			SqlC = " and  GameNameid='" + RoomSmallID + "'";
			para = "sid=" + RoomSmallID;
		}
		else
		{
			//Limit.outMsgBox( "温馨提示：\\n\\n请勿非法操作！", true );
			CommonManager.Web.RegJs( this, "alert('请勿非法操作！');", false );
			return;
		}

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "Web_VGameRoomInfo" )
		   .AddInputParameter( "@Wheres", DbType.String, SqlW )
		   .AddInputParameter( "@KeyName", DbType.String, "id" )
		   .AddInputParameter( "@OrderBy", DbType.String, "id desc" )
		   .ToDataSet();

		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			RoomListInfos.DataSource = ds.Tables[1];
			RoomListInfos.DataBind();
			RoomListInfos.Visible = true;
			NoRoomListInfos.Visible = false;
		}
		else
		{
			RoomListInfos.Visible = false;
			NoRoomListInfos.Visible = true;
		}

		/*
        DataTable sd = new DataTable();
        //string para = "bid=" + RoomBigID + "&sid=" + RoomSmallID;
        string[] sql = new string[2];
        sql[0] = "select * from TGameRoomInfo as a  left outer join TGameRoomBase as b on b.RoomID = a.RoomID " + SqlW + " order by ID DESC";
        sql[1] = "select count(*)  from TGameRoomInfo " + SqlC + "";
        string url = "GameRooms.aspx";
        PageLink page_set = new PageLink(url, 20, 10, para, sql);
        page_set.paraLinkType = paraLinkShow.middling.ToString();
        sd = page_set.get_table();
        if (sd.Rows.Count > 0)
        {
            Repeater VList = (Repeater)Page.FindControl("RoomListInfos");
            VList.DataSource = sd;
            VList.DataBind();
            this.pageList.Text = page_set.pageList();
        }
        else
            this.NoRoomListInfos.Visible = true;
        sd.Clear();*/
    }

    public string GetGameRooms(int SqlGameRooms)
    {
        switch (SqlGameRooms)
        {
            case 1:
                return "积分场";

            case 2:
                return "比赛场";

            case 3:
                return "金币场";
        }
        return "积分场";
    }


}
