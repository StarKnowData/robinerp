using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Collections;

using System.Text;
using Bzw.Data;
using Bzw.Entities;
using System.Data.SqlClient;
using Utility;
using Bzw.WebLibrary;
using BLL;
using System.IO;


namespace Bzw.Inhersits
{
	
	public partial class Default2:UiCommon.BasePage
	{
		protected HtmlHead Head1;

		/// <summary>
		/// webmeta1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected UserControl webmeta1;

		/// <summary>
		/// webtop1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected UserControl webtop1;

		/// <summary>
		/// webuserlogin1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected UserControl webuserlogin1;

		/// <summary>
		/// webservice1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected UserControl webservice1; 
	 
		/// <summary>
		/// rpNewHuoDong 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
        protected Repeater rptNews;


        protected Repeater rptQuesNews;

		/// <summary>
		/// odjDataHuoDong 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected ObjectDataSource odjDataHuoDong;

		/// <summary>
		/// rpNewGame 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		//protected Repeater rpNewGame;

		/// <summary>
		/// odjDataGame 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected ObjectDataSource odjDataGame;

	 

		/// <summary>
		/// odjDataSystem 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected ObjectDataSource odjDataSystem;

		/// <summary>
		/// rpDaoJu 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		//protected Repeater rpDaoJu;

		/// <summary>
		/// rptUserPicList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
        protected Repeater rptPhotoList;

		/// <summary>
		/// webshortcutkey1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		//protected Public_WebShortCutKey webshortcutkey1;

		/// <summary>
		/// rpCaifu 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		 protected Repeater rpCaifu;

         protected Repeater rpMeili;

         protected Repeater rptLotteries;

         protected Repeater rptGameTime;

         protected Repeater rptGameRank;

         protected Repeater rptMatchRank1;
         protected Repeater rptMatchRank2;
         protected Repeater rptMatchRank3;
         protected Repeater rptMatchRank4;
         protected Repeater rptMatchRank5;
		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected UserControl webfooter1;

        //protected Repeater rptGame1;
        //protected Repeater rptGame2;
        //protected Repeater rptGame3;

		 public int CaifuNo = 0;
    protected string fullUrl = "";

    protected DataTable AdsDT;

    protected DataRow UserPhotoNews;

	public int rankid = 0;

    public int helpid = 0;
    public BLL.Member member = new BLL.Member();
    protected void Page_Load(object sender, EventArgs e)
    {
        //Seo seo = SeoConfig.Config.IndexSeo;
        //Response.Write(string.IsNullOrEmpty(seo.Keyword) ? "a" : seo.Keyword);
        //Response.End();
        SeoSetting(SeoConfig.Config.IndexSeo);
        
		if (!IsPostBack)
		{
            //新闻动态
            BindNews();
            //常见问题
           BindQuesNews();
            //财富排行
           BindCaifu();
            //魅力值排行
           BindMeiliList();
            //奖券排行
           BindLotteriesList();
            //游戏时长排行
           BindGameTimeList();
            //最新五场比赛名
           BindTopFiveMatch();
            //玩家最新靓照
           InitUserAlbum();
           //绑定游戏列表
        //    BindGameList();
		}
    }
        //新闻动态
        public void BindNews()
        {
            rptNews.DataSource = (new BLL.News()).ListByTypeName("新闻动态", 8);
            rptNews.DataBind();
        }
         //常见问题
        public void BindQuesNews()
        {
            rptQuesNews.DataSource = (new BLL.News()).ListByTypeName("常见问题", 8);
            rptQuesNews.DataBind();
        }
        //魅力值排行
        public void BindMeiliList()
        {

            string where = " and meili>0";
            if (ConfigurationManager.AppSettings["RobotRank"] != null && ConfigurationManager.AppSettings["RobotRank"] == "0")
            {
                where += " and userid in (select userid from tusers where isrobot=0)";
            }
            int counts;
            DataTable dt = new BLL.Member().PagerListFascination(10, 1, out counts, where);

            rpMeili.DataSource = dt.DefaultView;
            rpMeili.DataBind();
        }
        //奖券排行
        public void BindLotteriesList()
        {
            DataTable dt = new BLL.Member().ListLotteries(10);
            rptLotteries .DataSource = dt.DefaultView;
            rptLotteries.DataBind();
        }
        //游戏时长排行
        public void BindGameTimeList()
        {
            DataTable dt = new BLL.Member().ListPlayTimeCount(10);
            rptGameTime.DataSource = dt.DefaultView;
            rptGameTime.DataBind();
        }
        /// <summary>
        /// 初始化最新玩家的最新照片
        /// </summary>
        private void InitUserAlbum()
        {
            //DataTable dt = DbSession.Default.FromSql("select top 20 * from Bzw_GetUserPic()").ToDataTable();
            DataTable dt = DbSession.Default.From<VUsersAlbum>().Where(VUsersAlbum._.Enable == Library.EnableState.通过.ToString() && VUsersAlbum._.IsPublic == Library.PublicState.公开.ToString()).OrderBy(VUsersAlbum._.InputTime.Desc).ToDataTable(20);
            if (dt.Rows.Count > 0)
            {
                rptPhotoList.DataSource = dt;
                rptPhotoList.DataBind();
            }
        }
        /// <summary>
        /// 最新5场比赛名 
        /// </summary>
        private void BindTopFiveMatch()
        {
            
            DataTable dt = DbSession.Default.FromSql("select top 5 Name,ContestID from Web_VTContestRoom where  EndTime<getdate() and comName is not null order by startTime desc").ToDataTable();
            rptGameRank.DataSource = dt.DefaultView;
            rptGameRank.DataBind();
            if (dt.Rows.Count > 0)
            {
                int i = 0;
                Game gm = new Game();
                foreach (DataRow row in dt.Rows)
                {
                    switch (i) {
                        case 0: rptMatchRank1.DataSource = gm.GetMatchRankDetail(row["ContestID"].ToString()); rptMatchRank1.DataBind(); break;
                        case 1: rptMatchRank2.DataSource = gm.GetMatchRankDetail(row["ContestID"].ToString()); rptMatchRank2.DataBind(); break;
                        case 2: rptMatchRank3.DataSource = gm.GetMatchRankDetail(row["ContestID"].ToString()); rptMatchRank3.DataBind(); break;
                        case 3: rptMatchRank4.DataSource = gm.GetMatchRankDetail(row["ContestID"].ToString()); rptMatchRank4.DataBind(); break;
                        case 4: rptMatchRank5.DataSource = gm.GetMatchRankDetail(row["ContestID"].ToString()); rptMatchRank5.DataBind(); break;
                        default: break;
                    }
                    i++;
                }

            }
            
        }
        //
        //public void BindGameList()
        //{
        //    Game game = new Game();
        //    rptGame1.DataSource = game.GetGameInfoList(0, 1);
        //    rptGame1.DataBind();
        //    rptGame2.DataSource = game.GetGameInfoList(0, 2);
        //    rptGame2.DataBind();
        //    rptGame3.DataSource = game.GetGameInfoList(0, 3);
        //    rptGame3.DataBind();
        //}
 
 

	 

	 
    //绑定热门游戏列表
    //public void BindHotGame()
    //{
    //    rpHotGameList.DataSource = new BLL.Game().List(5, 1).DefaultView;
    //    rpHotGameList.DataBind();
    //}

    //public void BindAllGame()
    //{
    //    rpAllGameList.DataSource = new BLL.Game().List(16, 0).DefaultView;
    //    rpAllGameList.DataBind();
    //}
    /*
    /// <summary>
    /// 绑定玩家鲜花排行
    /// </summary>
    private void BindTopFollows()
    {
        DataTable dt = DbSession.Default.FromSql("select TOP 7 * from Web_vFaciSum order by fascisum desc").ToDataTable();
        if (dt.Rows.Count > 0)
        {
            rptFollowsTop.Visible = true;
            ltNonFollows.Visible = false;
            rptFollowsTop.DataSource = dt;
            rptFollowsTop.DataBind();
        }
        else
        {
            rptFollowsTop.Visible = false;
            ltNonFollows.Visible = true;
        }
    }

    /// <summary>
    /// 绑定新闻栏目列表
    /// </summary>
    private void BindNewsColumn()
    {
        //DataTable dt = ( new BLL.News() ).TypeList(4);
        //if( dt.Rows.Count > 0 )
        //{
        //    ltNonNewsColumn.Visible = false;
        //    rptNewsColumnList.Visible = true;
        //    rptNewsColumnList.DataSource = dt;
        //    rptNewsColumnList.DataBind();
        //}
        //else
        //{
        //    ltNonNewsColumn.Visible = true;
        //    rptNewsColumnList.Visible = false;
        //}
    }

 

    //兑奖名单
    public void BindDuiJiangLog()
    {
        //rpDuiJingLog.DataSource = new BLL.Member().ListDuiJiangLog(6);
        //rpDuiJingLog.DataBind();
    }

  

    //绑定奖品数据 杨大胜 2009-4-14
    public void BindJiangPin()
    {
        
        <asp:Repeater ID="rpJiangPin" runat="server" Visible="false">
            <ItemTemplate>
                <tr>
                    <td>
                        <a href="/DuiJiang.aspx?id=<%#Eval("Award_ID") %>">
                            <img src="<%#Eval("Award_Pic") %>" alt="<%#Eval("Award_Name") %>" onerror="this.src='/Images/NoPicture/no_pic.gif'" height="100" width="265" /></a></td>
                </tr>
            </ItemTemplate>
            <SeparatorTemplate>
                <tr>
                    <td>
                        &nbsp;</td>
                </tr>
            </SeparatorTemplate>
        </asp:Repeater>
         

        //DataTable dt = new BLL.JiangPin().List(3);
        //rpJiangPin.DataSource = dt.DefaultView;
        //rpJiangPin.DataBind();
    }

    //绑定道具数据 杨大胜 2009-4-13
    public void BindDaoJu()
    {
        //DataTable dt = new BLL.DaoJu().List( 4 );
        //rpDaoJu.DataSource = dt.DefaultView;
        //rpDaoJu.DataBind();
    }

    //绑定友情链接 杨大胜 2009-4-23
    public void BindFriend()
    {
        //rpFriend.DataSource = new BLL.FriendLink().List(0);
        //rpFriend.DataBind();
    }
        */
        //玩家财富排行
        public void BindCaifu()
        {
            DataTable dt = new BLL.Member().ListCaifu(10);
            rpCaifu.DataSource = dt.DefaultView;
            rpCaifu.DataBind();
        }
    //生成Flash广告的JS代码 杨大胜 2009-4-12
    public string GetFlashJS(int width, int height, int adCount)
    {
        //:<<<<=高度注意=>>>>:
        //只支持JPG格式的图片，如果把GIF或其他格式的图片文件的扩展名直接改成JPG也不行
        //如果网站设置的端口有冲突的时，该FLASH不能正常显示，只有灰屏
        string xmlPath = Server.MapPath("/Upload/xml/flash.xml");
        if (!File.Exists(xmlPath))
        {
            return "请到网站后台Flash管理中添加记录";
        }

        DataSet ds = new DataSet();
        ds.ReadXml(xmlPath);
        DataTable dt =ds.Tables[0];
        if (dt.Rows.Count > 0)
        {
            //JS: 
            //<script>
            //var flash = new flashPlayer(311, 263, 0);
            //flash.add('图片路径', '链接地址', 'Title'); 
            //flash.play();
            //</script>
            StringBuilder sb = new StringBuilder();
            sb.Append("<script type=\"text/javascript\">");
            sb.Append("\n<!--");
            sb.Append("\nvar flash = new flashPlayer(" + width + ", " + height + ", 0);");
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                sb.Append("\nflash.add('" + dt.Rows[i]["item_url"] + "', '" + dt.Rows[i]["link"] + "', '" + dt.Rows[i]["itemtitle"] + "');");
            }

            sb.Append("\nflash.play();");
            sb.Append("\n//-->");
            sb.Append("\n</script>");

            return sb.ToString();
        }

        return "请到网站后台Flash管理中添加记录";
    }
	}
}
