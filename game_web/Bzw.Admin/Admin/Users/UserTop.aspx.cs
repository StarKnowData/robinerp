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
public partial class Admin_Users_UserTop : AdminBasePage
{
    string  ComName;
    string ids;
    public int listids = 0;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("04");

        DataTable sdt = new DataTable();
        string sqlt = "select NameID,ComName from TGameNameInfo where Enable=1 ";
		sdt = DbSession.Default.FromSql( sqlt ).ToDataTable(); //sqlconn.sqlReader(sqlt);
        if (sdt.Rows.Count > 0)
        {
			GameLists.DataSource = sdt;
			GameLists.DataBind();
        }
        else
            this.NoGameList.Visible = true;
        sdt.Clear();

		ids = CommonManager.Web.Request( "id", "" ); //Limit.editCharacter(Limit.getFormValue("id"));
        if (ids.ToString() == "") ids = "1001";
        if (ids != "")
        {
            DataTable sd2 = new DataTable();
            string sql2 = "select ComName from TGameNameInfo where NameID=" + ids + "";
            //Response.Write(sql2 + "<br>");
			sd2 = DbSession.Default.FromSql( sql2 ).ToDataTable(); //sqlconn.sqlReader(sql2);
			if( sd2.Rows.Count > 0 )
			{
				this.ComName = sd2.Rows[0]["ComName"].ToString();

			}
			else
			{
				//Limit.outMsgBox( "温馨提示：\\n\\n 暂无任何记录！", true );
				CommonManager.Web.RegJs( this, "alert('暂无任何记录。');", false );
				return;
			}
        }
        else
		{
			CommonManager.Web.RegJs( this, "alert('参数传递错误。');", false );
			return;
        }
        sdt.Clear();
        DataTable sd = new DataTable();
        //string sqlActive = "select top 30 u.name as name,r.win as win,r.lost as lost,r.cut as cut,r.PlayTimeCount as PlayTimeCount";
        //sqlActive = sqlActive + ",r.OnLineTimeCount as OnLineTimeCount,r.point as point from " + SearchTable + " as r,Users as u where u.userid=r.userid order by point desc";
		string sqlActive = "select * from Web_VMatchTable where Nameid=" + ids + "";
        //Response.Write(sqlActive);
		sd = DbSession.Default.FromSql( sqlActive ).ToDataTable(); //sqlconn.sqlReader(sqlActive);
        //Response.End();
        if (sd.Rows.Count > 0)
        {
			ListsInfo.DataSource = sd;
			ListsInfo.DataBind();
        }
        else
            this.NoList.Visible = true;
        sd.Clear();
    }
}
