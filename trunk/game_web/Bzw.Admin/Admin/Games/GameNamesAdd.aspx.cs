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

public partial class Admin_Games_GameNamesAdd : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

        if (!IsPostBack)
        {
            //绑定游戏类别
            DataTable sd = new DataTable();
            string sql = "select * from TGameKindInfo where parentkindid=0 order by kindid desc";
			sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
            if (sd.Rows.Count > 0)
            {
                this.KindID.DataBind();
                for (int i = 0; i < sd.Rows.Count; i++)
                {
                    this.KindID.Items.Add(new ListItem(sd.Rows[i]["kindname"].ToString(), sd.Rows[i]["kindid"].ToString()));
                }
            }
            sd.Clear();
            BindChildKind(this.KindID.Items[0].Value);
        }

    }

    protected void GameNaemAdd(object sender, EventArgs e)
    {
        string sqlKindID, sqlComName, sqlNameID, sqlIDSort, sqlComProcess, sqlEnable;

        string sqlDLLFileName, sqlDeskPeople,sqlEveryDayRent;
        
        //游戏ID号
		sqlNameID = CommonManager.Web.RequestForm( "NameID", "" ); //Limit.editCharacter(Limit.getFormValue("NameID"));
        //游戏名称
		sqlComName = CommonManager.Web.RequestForm( "ComName", "" ); //Limit.editCharacter(Limit.getFormValue("ComName"));
        //房间每天租金
        sqlEveryDayRent = CommonManager.Web.RequestForm("EveryDayRent", "0");
        if (!CommonManager.String.IsFloat(sqlEveryDayRent))
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

        string sql = @"insert TGameNameInfo (NameID,ComName,KindID,IDSort,ComProcess,Enable,EveryDayRent) 
						values (@NameID,@ComName,@KindID,@IDSort,@ComProcess,@Enable,@EveryDayRent);

						insert TGameServerInfo (ServerInfoID,NameID,GameName,DLLFileName,DeskPeople,GameTable,SupportType,ServiceVer) 
						values (@NameID,@NameID,@ComName,@DLLFileName,@DeskPeople,'MatchTable',2,2);";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@NameID", DbType.String, sqlNameID )
			.AddInputParameter( "@ComName", DbType.String, sqlComName )
			.AddInputParameter( "@KindID", DbType.String, sqlKindID )
			.AddInputParameter( "@IDSort", DbType.String, sqlIDSort )
			.AddInputParameter( "@ComProcess", DbType.String, sqlComProcess )
			.AddInputParameter( "@Enable", DbType.String, sqlEnable )
            .AddInputParameter( "@EveryDayRent", DbType.Int64, sqlEveryDayRent)
			.AddInputParameter( "@DLLFileName", DbType.String, sqlDLLFileName )
			.AddInputParameter( "@DeskPeople", DbType.String, sqlDeskPeople )
			.Execute();

		CommonManager.Web.RegJs( this, "alert('操作成功！');location.href='GameNames.aspx';", false );

		/*
        Hashtable ind = new Hashtable();
        ind.Add("NameID", sqlNameID);
        ind.Add("ComName", sqlComName);
        ind.Add("KindID", sqlKindID);
        ind.Add("IDSort", sqlIDSort);
        ind.Add("ComProcess", sqlComProcess);
        ind.Add("Enable", sqlEnable);
        int SqlState = sqlconn.sqlExecute(ind, "[TGameNameInfo]", 1);
        ind.Clear();

        ind.Add("ServerInfoID", sqlNameID);
        ind.Add("NameID", sqlNameID);
        ind.Add("GameName", sqlComName);
        ind.Add("DLLFileName", sqlDLLFileName);
        ind.Add("DeskPeople", sqlDeskPeople);
        ind.Add("GameTable", "MatchTable");
        ind.Add("SupportType", "2");
        ind.Add("ServiceVer", "2");
        SqlState += sqlconn.sqlExecute(ind, "[TGameServerInfo]", 1);
        ind.Clear();


        if (SqlState == 2)
            Limit.outMsgBox("温馨提示：\\n\\n游戏信息添加成功！", "GameNames.aspx", true);
        else
            Limit.outMsgBox("温馨提示：\\n\\n游戏信息添加失败！", true);*/

    }

    protected void KindID_SelectedIndexChanged(object sender, EventArgs e)
    {
    
        BindChildKind(KindID.SelectedValue);
    }
    private void BindChildKind(string pid)
    {
        //绑定游戏类别
        DataTable sd = new DataTable();
        string sql = "select * from TGameKindInfo where parentkindid="+pid+" order by kindid desc";
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

   
}
