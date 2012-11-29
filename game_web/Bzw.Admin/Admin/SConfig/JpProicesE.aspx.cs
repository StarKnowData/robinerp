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
using Utility;
using BCST.Common;
using Bzw.Data;

public partial class Admin_SConfig_JpProicesE : AdminBasePage
{
	string PropID;
    public string PropName, Price, VipPrice, Descript, Fasic, HidFasic;
	protected void Page_Load( object sender, EventArgs e )
	{
		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			PropID = tmp;
		DataTable sd = new DataTable();
		string sql = "select *  from TPropDefine where PropID=" + PropID + "";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); 
		if( sd.Rows.Count > 0 )
		{
			PropName = sd.Rows[0]["PropName"].ToString();
			Price = sd.Rows[0]["Price"].ToString();
			VipPrice = sd.Rows[0]["VipPrice"].ToString();
			Descript = sd.Rows[0]["Descript"].ToString();
            HidFasic = sd.Rows[0]["ValueAttribute"].ToString();
            Fasic = Convert.ToInt32(Convert.ToInt32( Convert.ToInt32(sd.Rows[0]["ValueAttribute"].ToString()) / Math.Pow(2, 16)) % (Math.Pow(2, 8))).ToString();
		}
		sd.Clear();
	}

	protected void EditJpPro( object sender, EventArgs e )
	{
		string   sqlPrice, sqlVipPrice, sqlDescript,sqlFasic;
		//sqlPropName = CommonManager.Web.RequestForm( "PropName", "" );
		sqlPrice = CommonManager.Web.RequestForm( "Price", "" );
		sqlVipPrice = CommonManager.Web.RequestForm( "VipPrice", "" );
		sqlDescript = CommonManager.Web.RequestForm( "Descript", "" );
        sqlFasic = CommonManager.Web.RequestForm("Fasic", "0");
        if (Convert.ToInt32(sqlFasic) < 0 || Convert.ToInt32(sqlFasic) > 255)
        {
            Alert("温馨提示：\\n\\n魅力值在0-255间！", null);
            return;
        }
		if( sqlDescript.Trim().Length > 25 )
		{
			Alert( "温馨提示：\\n\\n道具说明的字符个数不能超过25！", null );
			return;
		}
        Int32 fasic = Convert.ToInt32(sqlFasic);
        Int32 oldfasic = Convert.ToInt32(CommonManager.Web.RequestForm("hidv", ""));
        Int32 va =Convert.ToInt32( Convert.ToInt32(oldfasic / Math.Pow(2, 24)) * Math.Pow(2, 24))+Convert.ToInt32( fasic * Math.Pow(2, 16)) +Convert.ToInt32( oldfasic % (Math.Pow(2, 16)));
         
//        string sql = @"UPDATE [TPropDefine] SET 
//	[PropName] = @PropName,[Price] = @Price,[VipPrice] = @VipPrice,[Descript] = @Descript
//	WHERE PropID=@PropID ";
		string sql = @"UPDATE [TPropDefine] SET 
	[Price] = @Price,[VipPrice] = @VipPrice,[Descript] = @Descript,[ValueAttribute]=@ValueAttribute
	WHERE PropID=@PropID ";

		int SqlState = DbSession.Default.FromSql( sql )			
			.AddInputParameter( "@Price", DbType.String, sqlPrice )
			.AddInputParameter( "@VipPrice", DbType.String, sqlVipPrice )
			.AddInputParameter( "@Descript", DbType.String, sqlDescript )
			.AddInputParameter( "@PropID", DbType.String, PropID )
            .AddInputParameter("@ValueAttribute",DbType.Int32,va)
			.Execute();

		string adminName = AdminInfo["UserName"].ToString();
		string descript = "修改道具价格！";
		string system = Common.GetOS;
		if( SqlState >= 0 )
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 1 );
			Alert( "温馨提示：\\n\\n修改道具价格成功！", "JpPrices.aspx" );
		}
		else
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 0 );
			Alert( "温馨提示：\\n\\n修改道具价格失败！", null );
		}

	}
}
