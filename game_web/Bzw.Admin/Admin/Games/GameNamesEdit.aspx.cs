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
using BCST.Common;
using Bzw.Data;

public partial class Admin_Games_GameNamesEdit : AdminBasePage
{
	string nameids = "";
    public string ComName = "", NameID = "", IDSort = "", ComProcess = "", MatchTable = "", Enable = "", DLLFileName = "", DeskPeople = "", EveryDayRent = "";

    public string RoomBigID;
    string RoomSmallID;
    string sqlwhere;
    string SqlW, SqlC;
    public int tableids;
    string para = "";
    public int ddlKinkId = 0;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );

		if( !IsPostBack )
		{
			//Limit.editCharacter( Limit.getFormValue( "id" ) );

            GameNameInfo();

			DataTable sd2 = new DataTable();
			string sql2 = "select * from TGameKindInfo   order by KindId desc";
			sd2 = DbSession.Default.FromSql( sql2 ).ToDataTable(); //sqlconn.sqlReader( sql2 );
			if( sd2.Rows.Count > 0 )
			{
				this.KindID.DataBind();
                this.KindID.Items.Clear();
				for( int i = 0; i < sd2.Rows.Count; i++ )
				{
                    if (sd2.Rows[i]["ParentKindID"].ToString() == "0")
                    {
                        this.KindID.Items.Add(new ListItem(sd2.Rows[i]["KindName"].ToString(), sd2.Rows[i]["KindId"].ToString()));
                        if (ddlKinkId == Convert.ToInt32(sd2.Rows[i]["KindId"]))
                        {
                            this.KindID.SelectedValue = ddlKinkId.ToString();
                            BindChildKind(this.KindID.SelectedValue);
                        }

                    }
                    else {
                        if (ddlKinkId == Convert.ToInt32(sd2.Rows[i]["KindID"]))
                        {
                            this.KindID.SelectedValue = sd2.Rows[i]["ParentKindID"].ToString();
                            BindChildKind(sd2.Rows[i]["ParentKindID"].ToString());
                            this.ChildKindID.SelectedValue = ddlKinkId.ToString();
                        }
                    }
                    
				}

			}
			sd2.Clear();
            GameRoom();
		}
	}
    protected void GameNameInfo()
    {
        string tmp = CommonManager.Web.Request("id", "");
        if (string.IsNullOrEmpty(tmp) || !CommonManager.String.IsInteger(tmp))
        {
            CommonManager.Web.RegJs(this, "alert('请勿非法操作！');", false);
            return;
        }
        else
            nameids = tmp;
        DataTable sd = new DataTable();
        string sql = @"select * from Web_VGameNameInfo where NameID=" + nameids;
        sd = DbSession.Default.FromSql(sql).ToDataTable(); //sqlconn.sqlReader( sql );

        if (sd.Rows.Count > 0)
        {
            this.NameID = sd.Rows[0]["NameID"].ToString();
            this.ComName = sd.Rows[0]["ComName"].ToString();

            ddlKinkId = Convert.ToInt32(sd.Rows[0]["KindId"]);
            this.IDSort = sd.Rows[0]["IDSort"].ToString();
            this.ComProcess = sd.Rows[0]["ComProcess"].ToString();
            this.Enable = sd.Rows[0]["Enable"].ToString();
            this.EveryDayRent = sd.Rows[0]["EveryDayRent"].ToString();

            this.DLLFileName = sd.Rows[0]["DLLFileName"].ToString();
            this.DeskPeople = sd.Rows[0]["DeskPeople"].ToString();
        }
        sd.Clear();
    }
	protected void GameNamesEdit( object sender, EventArgs e )
	{
		nameids = CommonManager.Web.Request( "id", "" );//Limit.editCharacter( Limit.getFormValue( "id" ) );

		string sqlKindID, sqlComName, sqlNameID, sqlIDSort, sqlComProcess, sqlEnable;
        string sqlDLLFileName, sqlDeskPeople, sqlEveryDayRent;

		//游戏ID号
		sqlNameID = CommonManager.Web.RequestForm( "NameID", "" ); //Limit.editCharacter(Limit.getFormValue("NameID"));
		//游戏名称
		sqlComName = CommonManager.Web.RequestForm( "ComName", "" ); //Limit.editCharacter(Limit.getFormValue("ComName"));
        //房间每天租金
        sqlEveryDayRent = CommonManager.Web.RequestForm("EveryDayRent", "");
        if (sqlEveryDayRent.ToString() == "" || !CommonManager.String.IsFloat(sqlEveryDayRent))
        {
            Alert("温馨提示：\\n\\n房间每天租金只能为数字！", null);
            return;
        }
		//-----------------客户端资料-----------------------------
		//游戏类别 
        if (CommonManager.Web.RequestForm("ChildKindID", "") == "0")
        {
            sqlKindID = CommonManager.Web.RequestForm("KindID", ""); //Limit.editCharacter(Limit.getFormValue("KindID"));
        }
        else
        {
            sqlKindID = CommonManager.Web.RequestForm("ChildKindID", "");
        }
		//排列号
		sqlIDSort = CommonManager.Web.RequestForm( "IDSort", "" ); //Limit.editCharacter(Limit.getFormValue("IDSort"));
		//客户端ICO文件名
		sqlComProcess = CommonManager.Web.RequestForm( "ComProcess", "" ); //Limit.editCharacter(Limit.getFormValue("ComProcess"));
		//是否激活
		sqlEnable = CommonManager.Web.RequestForm( "Enable", "" ); //Limit.editCharacter(Limit.getFormValue("Enable"));

		//-----------------服务器资料-----------------------------
		//服务端文件名
		sqlDLLFileName = CommonManager.Web.RequestForm( "DLLFileName", "" ); //Limit.editCharacter(Limit.getFormValue("DLLFileName"));
		//桌子人数
		sqlDeskPeople = CommonManager.Web.RequestForm( "DeskPeople", "" ); //Limit.editCharacter(Limit.getFormValue("DeskPeople"));

		string sql = @"update TGameNameInfo set ComName=@ComName,
						KindID=@KindID,IDSort=@IDSort,ComProcess=@ComProcess,Enable=@Enable,EveryDayRent=@EveryDayRent where NameID=@NameID;
						update TGameServerInfo set GameName=@ComName,DLLFileName=@DLLFileName,DeskPeople=@DeskPeople where NameID=@NameID;";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@NameID", DbType.String, sqlNameID )
			.AddInputParameter( "@ComName", DbType.String, sqlComName )
			.AddInputParameter( "@KindID", DbType.String, sqlKindID )
			.AddInputParameter( "@IDSort", DbType.String, sqlIDSort )
			.AddInputParameter( "@ComProcess", DbType.String, sqlComProcess )
			.AddInputParameter( "@Enable", DbType.String, sqlEnable )
            .AddInputParameter( "@EveryDayRent", DbType.Int64, sqlEveryDayRent)
            .AddInputParameter( "@DLLFileName", DbType.String, sqlDLLFileName)
			.AddInputParameter( "@DeskPeople", DbType.String, sqlDeskPeople )
			.Execute();

		CommonManager.Web.RegJs( this, "alert('操作成功！');location.href='GameNames.aspx';", false );

		/*
		sqlComName = Limit.editCharacter( Limit.getFormValue( "ComName" ) );

		sqlKindID = Limit.editCharacter( Limit.getFormValue( "KindID" ) );
		sqlIDSort = Limit.editCharacter( Limit.getFormValue( "IDSort" ) );
		sqlComProcess = Limit.editCharacter( Limit.getFormValue( "ComProcess" ) );
		sqlEnable = Limit.editCharacter( Limit.getFormValue( "Enable" ) );

		//-----------------服务器资料-----------------------------
		//服务端文件名
		sqlDLLFileName = Limit.editCharacter( Limit.getFormValue( "DLLFileName" ) );
		//桌子人数
		sqlDeskPeople = Limit.editCharacter( Limit.getFormValue( "DeskPeople" ) );

		Hashtable ind = new Hashtable();
		ind.Add( "ComName", sqlComName );
		ind.Add( "KindID", sqlKindID );
		ind.Add( "IDSort", sqlIDSort );
		ind.Add( "ComProcess", sqlComProcess );
		ind.Add( "Enable", sqlEnable );
		int SqlState = sqlconn.sqlExecute( ind, "[TGameNameInfo]", "NameID=" + nameids + "", 2 );
		ind.Clear();

		ind.Add( "GameName", sqlComName );
		ind.Add( "DLLFileName", sqlDLLFileName );
		ind.Add( "DeskPeople", sqlDeskPeople );

		SqlState += sqlconn.sqlExecute( ind, "[TGameServerInfo]", "NameID=" + nameids + "", 2 );
		ind.Clear();

		if( SqlState == 2 )
			Limit.outMsgBox( "温馨提示：\\n\\n游戏信息修改成功！", "GameNames.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n游戏信息修改失败！", true );
		*/
	}
    /// <summary>
    /// 游戏房间
    /// </summary>
    protected void GameRoom()
    {
        AdminPopedom.IsHoldModel("06");

        DataTable sdBig = new DataTable();
        string sqlBig = "select * from TGameKindInfo order by IDSort desc";
        sdBig = DbSession.Default.FromSql(sqlBig).ToDataTable(); //sqlconn.sqlReader(sqlBig);
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

        RoomBigID = CommonManager.Web.Request("bid", "");//Limit.getFormValue("bid");

        if (RoomBigID.ToString() == "")
        {
            sqlwhere = " order by IDSort DESC";
        }
        else
            sqlwhere = "where KindID=" + RoomBigID + " order by IDSort DESC";

        DataTable sdSmall = new DataTable();
        string sqlSmall = "select NameID,ComName from TGameNameInfo " + sqlwhere + "";
        sdSmall = DbSession.Default.FromSql(sqlSmall).ToDataTable(); //sqlconn.sqlReader(sqlSmall);
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
        if (CommonManager.Web.Request("id", "") == "")
        {
            RoomSmallID = CommonManager.Web.Request("sid", "");//Limit.getFormValue("sid");
        }
        else
        {
            RoomSmallID = CommonManager.Web.Request("id", "");
        }
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
        else if (RoomSmallID.ToString() != "")
        {
            SqlW = " and  GameNameid='" + RoomSmallID + "'";
            SqlC = " and  GameNameid='" + RoomSmallID + "'";
            para = "sid=" + RoomSmallID;
        }
        else
        {
            //Limit.outMsgBox( "温馨提示：\\n\\n请勿非法操作！", true );
            CommonManager.Web.RegJs(this, "alert('请勿非法操作！');", false);
            return;
        }

        DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
           .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
           .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
           .AddInputParameter("@Columns", DbType.String, "*")
           .AddInputParameter("@TableName", DbType.String, "Web_VGameRoomInfo")
           .AddInputParameter("@Wheres", DbType.String, SqlW)
           .AddInputParameter("@KeyName", DbType.String, "id")
           .AddInputParameter("@OrderBy", DbType.String, "IDSort desc,id desc")
           .ToDataSet();

        if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
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
    private void BindChildKind(string pid)
    { 
        //绑定游戏类别
        DataTable sd = new DataTable();
        string sql = "select * from TGameKindInfo where parentkindid=" + pid + " order by kindid desc";
        sd = DbSession.Default.FromSql(sql).ToDataTable(); //sqlconn.sqlReader(sql);
        this.ChildKindID.Items.Clear();
        this.ChildKindID.Items.Add(new ListItem("无", "0"));
        if (sd.Rows.Count > 0)
        {
            this.ChildKindID.DataBind();

            for (int i = 0; i < sd.Rows.Count; i++)
            {
                this.ChildKindID.Items.Add(new ListItem(sd.Rows[i]["kindname"].ToString(), sd.Rows[i]["kindid"].ToString()));
            }
        }
        sd.Clear();
    }

    protected void KindID_SelectedIndexChanged(object sender, EventArgs e)
    {
        BindChildKind(KindID.SelectedValue);
        GameNameInfo();
    }
}
