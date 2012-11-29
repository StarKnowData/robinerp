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

public partial class Admin_Books_BookInfo : AdminBasePage
{
    string BookID;
    public string IsPass;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("02");
		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		//Limit.outMsgBox("温馨提示：\\n\\n请勿非法操作！", true);
		{
			CommonManager.Web.RegJs( this, "alert('请勿非法操作！');", false );
			return;
		}
		else
			BookID = tmp; //Limit.editCharacter(Limit.getFormValue("id"));

        DataTable sd = new DataTable();
        string sql = "select * from web_msg where msgid=" + BookID + "";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0)
        {
            IsPass = sd.Rows[0]["ispass"].ToString();
			BookInfos.DataSource = sd;
			BookInfos.DataBind();
        }
        sd.Clear();
    }


    protected void HFBook(object sender, EventArgs e)
    {
		string Reply = CommonManager.Web.RequestForm( "Reply", "" );//Limit.editCharacter(Limit.getFormValue("Reply"));
		string inpIsPass = CommonManager.Web.RequestForm( "inp", "0" );//Limit.editCharacter(Limit.getFormValue("inp"));


		string sql = "update web_msg set ispass=@Pass";
		if( !string.IsNullOrEmpty( Reply ) )
			sql += ",MsgReply=@Reply,MsgReplyTime=getdate()";
		sql += " where msgid=@id";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@Pass", DbType.Int32, inpIsPass )
			.AddInputParameter( "@Reply", DbType.String, Reply )
			.AddInputParameter( "@id", DbType.Int32, BookID )
			.Execute();

		CommonManager.Web.RegJs( this, "alert('操作成功！');location.href='Book.aspx';", false );

		/*
		Hashtable ind = new Hashtable();
        if(Reply != "")
        {
            ind.Add("MsgReply", Reply);
            ind.Add("MsgReplyTime", DateTime.Now);
        }
        ind.Add("ispass", inpIsPass);
        int SqlState = sqlconn.sqlExecute(ind, "[web_msg]", "Msgid=" + BookID + "", 2);
        ind.Clear();
        if (SqlState > 0)
            Limit.outMsgBox("温馨提示：\\n\\n留言回复成功！", "Book.aspx", true);
        else
            Limit.outMsgBox("温馨提示：\\n\\n留言回复失败！", true);*/
    }
}
