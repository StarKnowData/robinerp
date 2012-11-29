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

public partial class Admin_SConfig_Filtering : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("12");

        if (!IsPostBack)
        {
            DataTable sd = new DataTable();
            string sql = "select top 1 * from Web_Config";
            sd = DbSession.Default.FromSql(sql).ToDataTable(); //sqlconn.sqlReader( sql );
            if (sd.Rows.Count > 0)
            {
                txtBadUserName.Text = sd.Rows[0]["BadUserName"].ToString();
                txtBadNickName.Text = sd.Rows[0]["BadNickName"].ToString();
                txtIPDisabled.Text = sd.Rows[0]["IPDisabled"].ToString();
                txtReRegTimeSpan.Text = sd.Rows[0]["ReRegTimeSpan"].ToString();
                this.txtSpecialUser.Text = sd.Rows[0]["SpecialUser"].ToString();
                txtSameIPRegCount.Text = sd.Rows[0]["SameIPRegCount"].ToString();
                txtSameCardNoRegCount.Text = sd.Rows[0]["SameCardNoRegCount"].ToString();
                
            }
            sd.Clear();
        }
    }

    protected void EditFilt(object sender, EventArgs e)
    {
        if (!CommonManager.Web.CheckPostSource())
            return;
        if (!IsValid)
            return;

        string sqlbadUserName, sqlbadNickName;
        sqlbadUserName = txtBadUserName.Text.Trim();
        if (sqlbadUserName.Trim().Length > 8000)
        {
            Alert("温馨提示：\\n\\n用户名中禁止包含的关键字的字符个数不能超过8000（4000个汉字）！", null);
        }
        sqlbadNickName = txtBadNickName.Text.Trim();
        if (sqlbadNickName.Trim().Length > 8000)
        {
            Alert("温馨提示：\\n\\n用户昵称中禁止包含的关键字的字符个数不能超过8000（4000个汉字）！", null);
        }
        if (txtIPDisabled.Text.Trim().Length > 2000)
        {
            Alert("温馨提示：\\n\\nIP限制输入的字符数不能超过2000个字符。", null);
        }
       
        if (!CommonManager.String.IsInteger(txtReRegTimeSpan.Text.Trim()))
        {
            Alert("温馨提示：\\n\\n重复注册时间设置应是大于或等于0的整数。", null);
        }


        string sql = @"update Web_Config set BadUserName=@BadUserName,
				BadNickName=@BadNickName,IpDisabled=@IpDisabled,
				ReRegTimeSpan=@ReRegTimeSpan,SpecialUser=@SpecialUser,SameIPRegCount=@SameIPRegCount,SameCardNoRegCount=@SameCardNoRegCount  where ID=1";

        DbSession.Default.FromSql(sql)
            .AddInputParameter("@BadUserName", DbType.String, txtBadUserName.Text.Trim())
            .AddInputParameter("@BadNickName", DbType.String, txtBadNickName.Text.Trim())
            .AddInputParameter("@IpDisabled", DbType.String, txtIPDisabled.Text.Trim())
            .AddInputParameter("@ReRegTimeSpan", DbType.String, txtReRegTimeSpan.Text.Trim())
            .AddInputParameter("@SpecialUser", DbType.String, txtSpecialUser.Text.Trim())
            .AddInputParameter("@SameIPRegCount",DbType.Int32,txtSameIPRegCount.Text.Trim())
            .AddInputParameter("@SameCardNoRegCount",DbType.Int32,txtSameCardNoRegCount.Text.Trim())
            .Execute();

        Alert("温馨提示：\\n\\n注册过滤设置成功！", "Filtering.aspx");

        /*
        Hashtable ind = new Hashtable();
        ind.Add("badUserName", sqlbadUserName);
        ind.Add("badNickName", sqlbadNickName);
        ind.Add( "IPDisabled", txtIPDisabled.Text.Trim() );
        ind.Add( "ReRegTimeSpan", txtReRegTimeSpan.Text.Trim() );
        int SqlState = sqlconn.sqlExecute(ind, "[Web_Config]", "id=1", 2);
        ind.Clear();
        if (SqlState > 0)
            Limit.outMsgBox("温馨提示：\\n\\n注册过滤设置成功！", "Filtering.aspx", true);
        else
            Limit.outMsgBox("温馨提示：\\n\\n注册过滤设置失败！", true);*/

    }
}
