using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using System.Data.SqlTypes;
using BCST.Common;


namespace Bzw.Web.Admin.FineryID
{
	public partial class IsBuyFineryID : AdminBasePage
	{
		public int TableID = 0;
		public string where = @" and IsBuy=0";
		protected void Page_Load( object sender, EventArgs e )
		{
			AdminPopedom.IsHoldModel( "14" );
			//接受搜索条件
			//AABB | AABBCC | ABAB | ABABAB | 3A | 4A | 5A及以上  | ABCABC | ABGAB | 4顺及以上 | 生日
			if( CommonManager.Web.Request( "sjCKB", "" )=="1" )
			{
				where +=" and IsSale=1";
			}
			if( CommonManager.Web.Request( "tjCKB", "" ) == "1" )
			{
				where += " and IsTop=1";
			}
			string type=CommonManager.Web.Request( "type", "" );
			string seacid = CommonManager.Web.Request("seachid","");
			if( !string.IsNullOrEmpty( seacid )||seacid!="" )
			{
				where += "and FineryID like '%" + seacid + "%'";
			}
			if( type == "aabb" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{1,}(\\d)\\2{1,}') = 1 and dbo.regex_ismatch(FineryID,'(\\d)\\1{1}(\\d)\\2{1}(\\d)\\3{1}') = 0";
			}
			if( type == "aabbcc" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{1}(\\d)\\2{1}(\\d)\\3{1}') = 1";
			}
			if( type == "abab" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(([\\d]){2})\\1{1}') = 1 and dbo.regex_ismatch(FineryID,'(\\d)\\1{1,}(\\d)\\2{1,}') = 0";
			}
			if( type == "ababab" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(([\\d]){2})\\1{2}') = 1 ";
			}
			if( type == "abcabc" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(([\\d]){3})\\1{1}') = 1";
			}
			if( type == "abgab" )
			{
				where += "and dbo.regex_ismatch(FineryID,'^((\\d){2,})\\d\\1{1}$') = 1";
			}
			if( type == "3a" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{2}')=1 and dbo.regex_ismatch(FineryID,'(\\d)\\1{3,}')= 0";
			}
			if( type == "4a" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{3}')=1 and dbo.regex_ismatch(FineryID,'(\\d)\\1{4,}')= 0";
			}
			if( type == "5a" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{4,}')=1";
			}
			if( type == "4sun" )
			{
				where += "and dbo.regex_ismatch(FineryID,'((?:0(?=1)|1(?=2)|2(?=3)|3(?=4)|4(?=5)|5(?=6)|6(?=7)|7(?=8)|8(?=9)){3}\\d)|((?:9(?=8)|8(?=7)|7(?=6)|6(?=5)|5(?=4)|4(?=3)|3(?=2)|2(?=1)|1(?=0)){3}\\d)')=1";
			}
			if( type == "date" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(19|20)[\\d]{2}((1[0-2])|(0[1-9]))((3[0-1])|(2[0-9])|(1[0-9])|(0[1-9]))')=1";
			}
			this.msg.Text = "";
			if(!IsPostBack)
			{
				BindFineryID();	
			}
		}
		//手动添加靓号
		protected void Button1_Click( object sender, EventArgs e )
		{
			this.msg.Text = "";
			string fineryid = this.FineryID.Text.ToString().Trim();
			string price = this.pr.Text.ToString().Trim();
			if( !Utility.Common.IsNumber( fineryid )|| fineryid.Length<2||fineryid.Length>9)
			{
				this.msg.Text = "很抱歉，靓号需为数字且长度为2-9位";
				return;
			}
			if( !Utility.Common.IsIntegrity( price ) )
			{
				this.msg.Text = "很抱歉，价格需为正整数";
				return;
			}
			//判断TUser或Web_FineryID表是否存在添加的靓号ID
			string sql = @"select * from Web_FineryID where FineryID=@FineryID
						   --insert into Web_FineryID(FineryID, Price, IsBuy, IsUse) values(@FineryID,'500',0,0)
						   --select UserID from Tusers from TUsers where UserID=@FineryID";
			object obj = DbSession.Default.FromSql( sql )
					.AddInputParameter( "@FineryID", DbType.Int32, fineryid )
					.ToScalar();
			int cout = Convert.ToInt32( obj );
			if(cout>0)
			{
				this.msg.Text = "很抱歉，靓号已存在或已被用户注册";
				return;
			}
			else
			{
				cout = 0;
				sql = @"insert into Web_FineryID(FineryID, Price, IsBuy, IsUse) values(@FineryID,@Price,0,0)";
				cout = DbSession.Default.FromSql( sql )
					.AddInputParameter( "@FineryID", DbType.Int32, fineryid )
					.AddInputParameter( "@Price", DbType.Int32, price )
					.Execute();
				if( cout > 0 )
				{
					this.msg.Text = "恭喜您,添加成功";
					BindFineryID();
				}
				else
				{
					this.msg.Text = "未知错误";
				}
				
			}
		}
		
		//初始绑定数据
		public void BindFineryID()
		{
			DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
				.AddInputParameter( "@Columns", DbType.String, "*" )
				.AddInputParameter( "@TableName", DbType.String, "Web_FineryID" )
				.AddInputParameter( "@Wheres", DbType.String, where )
				.AddInputParameter( "@KeyName", DbType.String, "DateTime" )
				.AddInputParameter( "@OrderBy", DbType.String, "DateTime desc" )
				.ToDataSet();

			if( ds.Tables.Count > 0 )
			{
				anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
				anpPageIndex.CurrentPageIndex = PageIndex;

				if( ds.Tables[1].Rows.Count > 0 )
				{
					FrineryIDList.Visible = true;
					NoProList.Visible = false;
					FrineryIDList.DataSource = ds.Tables[1];
					FrineryIDList.DataBind();
				}
				else
				{
					NoProList.Visible = false;
					FrineryIDList.Visible = true;
				}
			}
		}
	}
}
