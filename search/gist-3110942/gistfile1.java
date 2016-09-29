package ch4.lucenedemo.InitIndexSearch;
/** 
 * Title: 	 SetScoreClass
 * 
 * Description: Score 
 * 
 * Version:
 * 
 * Date：2012-7-13 *
 * @author Superman  
 * 
 */
import java.io.IOException;

import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryParser.MultiFieldQueryParser;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.FuzzyQuery;
import org.apache.lucene.search.Hits;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.MultiPhraseQuery;
import org.apache.lucene.search.MultiSearcher;
import org.apache.lucene.search.ParallelMultiSearcher;
import org.apache.lucene.search.PhraseQuery;
import org.apache.lucene.search.PrefixQuery;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.RangeQuery;
import org.apache.lucene.search.TermQuery;
import org.apache.lucene.search.WildcardQuery;
import org.apache.lucene.search.spans.SpanFirstQuery;
import org.apache.lucene.search.spans.SpanNearQuery;
import org.apache.lucene.search.spans.SpanOrQuery;
import org.apache.lucene.search.spans.SpanQuery;
import org.apache.lucene.search.spans.SpanTermQuery;

 
public class IndexSearch {
	private static String INDEX_STORE_PATH="E:\\test_index";
	private static String INDEX_STORE_PATH1="E:\\test_index";
	private static String INDEX_STORE_PATH2="K:\\test_index";
	/**
	 * @param args
	 * @throws ParseException 
	 */ 
		// TODO Auto-generated method stub 
	public static void main(String[] args) throws ParseException {
//		InitIndexSearchClass.SimpleExample();
//		SetScoreClass.myscore();
//		QueryClass.booleanQuery();
//		QueryClass.rangeQuery();
//		QueryClass.prefixQuery();
//		QueryClass.pharseQuery();
//		QueryClass.multiPharseQuery();
//		QueryClass.fuzzyQuery();
//		QueryClass.wildcardQuery();
//		QueryClass.spanQuery_SpanTermQuery();
//		QueryClass.spanQuery_SpanFirstQuery();
//		QueryClass.spanQuery_SpanNearQuery_1();
//		QueryClass.spanQuery_SpanNearQuery_2();
//		QueryClass.spanQuery_SpanOrQuery();
//		QueryClass.spanQuery_SpanNotQuery();
//		QueryClass.queryParse();
		ParallelMutilSearcherClass.parallelMutilSearcher();
	}
	private static class InitIndexSearchClass{
		public static void SimpleExample() {
			try {
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				Term term=new Term("bookname","女");
				 org.apache.lucene.search.Query query=new TermQuery(term);
				Hits hits=searcher.search(query);
				
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
			}catch(IOException ex) {
				ex.printStackTrace(); 
			}
		} 
	}

	private static class SetScoreClass{
		private static void myscore(){
			try {

				/**
				 * (词条频率)*(反转文档频率)*(激励因子)*(长度因子)
				 * */
				System.out.println("=================begin!=================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document();
				Field field=new Field("bookname","钢铁是怎样炼成的",Field.Store.YES,Field.Index.TOKENIZED);
				doc1.add(field);
				writer.addDocument(doc1);
				
				Document doc2=new Document();
				field=new Field("bookname","英雄儿女",Field.Store.YES,Field.Index.TOKENIZED);
				doc2.add(field);
				writer.addDocument(doc2);
				
				Document doc3=new Document();
				field=new Field("bookname","篱笆女人和狗",Field.Store.YES,Field.Index.TOKENIZED);
				/** 设置激励因子，降低文档的排名*/
				field.setBoost(0.1f);
				doc3.add(field);
				writer.addDocument(doc3);
				
				Document doc4=new Document();
				field=new Field("bookname","女人是水做的",Field.Store.YES,Field.Index.TOKENIZED);
				doc4.add(field);
				writer.addDocument(doc4);
				
				Document doc5=new Document();
				field=new Field("bookname","我的兄弟和女儿",Field.Store.YES,Field.Index.TOKENIZED);
				doc5.add(field);
				writer.addDocument(doc5);
				
				Document doc6=new Document();
				field=new Field("bookname","白毛女",Field.Store.YES,Field.Index.TOKENIZED);
				doc6.add(field);
				writer.addDocument(doc6);
				
				Document doc7=new Document();
				field=new Field("bookname","钢的世界",Field.Store.YES,Field.Index.TOKENIZED);
				doc7.add(field);
				writer.addDocument(doc7);
				
				Document doc8=new Document();
				field=new Field("bookname","钢铁战士",Field.Store.YES,Field.Index.TOKENIZED);
				doc8.add(field);
				writer.addDocument(doc8);
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				Term term=new Term("bookname","女");
				Query query=new TermQuery(term);
				Hits hits=searcher.search(query);
				for(int i=0;i<hits.length();i++) {
					System.out.println("索引内容   "+hits.doc(i));
					System.out.println("得分   "+hits.score(i));
					System.out.println("索引编号   "+hits.id(i));
					System.out.println("--------------------------------------");
				}
				
				
				System.out.println("================end!==================");
				
				}catch(IOException ex) { 
					ex.printStackTrace();
				}
			
		}

	
	}
	
	private static class QueryClass{
		
		//布尔搜索BooleanQuery
		private static void booleanQuery() {
			try {
					IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
					writer.setUseCompoundFile(false);
					
					Document doc1=new Document(); 
					Document doc2=new Document(); 
					Document doc3=new Document();					
					Document doc4=new Document(); 
					Document doc5=new Document();					
					Document doc6=new Document(); 
					Document doc7=new Document();
					Document doc8=new Document();
					
					Field field1=new Field("bookname","钢铁是怎样炼成的",Field.Store.YES,Field.Index.TOKENIZED);
					Field field2=new Field("bookname","英雄儿女",Field.Store.YES,Field.Index.TOKENIZED);
					Field field3=new Field("bookname","篱笆女人和狗",Field.Store.YES,Field.Index.TOKENIZED);
					Field field4=new Field("bookname","女人是水做的",Field.Store.YES,Field.Index.TOKENIZED);
					Field field5=new Field("bookname","我的兄弟和女儿",Field.Store.YES,Field.Index.TOKENIZED);
					Field field6=new Field("bookname","白毛女",Field.Store.YES,Field.Index.TOKENIZED);
					Field field7=new Field("bookname","钢的世界",Field.Store.YES,Field.Index.TOKENIZED);
					Field field8=new Field("bookname","钢铁战士",Field.Store.YES,Field.Index.TOKENIZED);
  
					doc1.add(field1);
					doc2.add(field2);
					doc3.add(field3);
					doc4.add(field4);
					doc5.add(field5);
					doc6.add(field6);
					doc7.add(field7);
					doc8.add(field8);
					
					writer.addDocument(doc1);
					writer.addDocument(doc2);
					writer.addDocument(doc3);
					writer.addDocument(doc4);
					writer.addDocument(doc5);
					writer.addDocument(doc6);
					writer.addDocument(doc7);
					writer.addDocument(doc8);
					
					writer.close();
					
					IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
					Term term1=new Term("bookname","女");
					Term term2=new Term("bookname","狗");
					Term term3=new Term("bookname","的");
					TermQuery query1=new TermQuery(term1);
					TermQuery query2=new TermQuery(term2);
					TermQuery query3=new TermQuery(term3);
					BooleanQuery query=new BooleanQuery();
					query.add(query1,BooleanClause.Occur.SHOULD);
					query.add(query2,BooleanClause.Occur.SHOULD);
					query.add(query3,BooleanClause.Occur.SHOULD);
					Hits hits=searcher.search(query);
					
					for(int i=0;i<hits.length();i++)
						System.out.println(hits.doc(i));
					
					
		 
			}catch(IOException ex){
				ex.printStackTrace();
			}
			
		}
	
		//范围搜索RangeQuery
		private static void rangeQuery() {
			try {
					IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
					writer.setUseCompoundFile(false);
					
					Document doc1=new Document(); 
					Document doc2=new Document(); 
					Document doc3=new Document();					
					Document doc4=new Document(); 
					Document doc5=new Document();					
					Document doc6=new Document(); 
					Document doc7=new Document();
					Document doc8=new Document(); 
					
					Field field1=new Field("bookname","0000001",Field.Store.YES,Field.Index.UN_TOKENIZED);
					Field field2=new Field("bookname","0000002",Field.Store.YES,Field.Index.UN_TOKENIZED);
					Field field3=new Field("bookname","0000003",Field.Store.YES,Field.Index.UN_TOKENIZED);
					Field field4=new Field("bookname","0000004",Field.Store.YES,Field.Index.UN_TOKENIZED);
					Field field5=new Field("bookname","0000005",Field.Store.YES,Field.Index.UN_TOKENIZED);
					Field field6=new Field("bookname","0000006",Field.Store.YES,Field.Index.UN_TOKENIZED);
					Field field7=new Field("bookname","0000007",Field.Store.YES,Field.Index.UN_TOKENIZED);
					Field field8=new Field("bookname","0000008",Field.Store.YES,Field.Index.UN_TOKENIZED); 
					
					doc1.add(field1);
					doc2.add(field2);
					doc3.add(field3);
					doc4.add(field4);
					doc5.add(field5);
					doc6.add(field6);
					doc7.add(field7);
					doc8.add(field8);
					
					writer.addDocument(doc1);
					writer.addDocument(doc2);
					writer.addDocument(doc3);
					writer.addDocument(doc4);
					writer.addDocument(doc5);
					writer.addDocument(doc6);
					writer.addDocument(doc7);
					writer.addDocument(doc8);
					
					writer.close();
					
					IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
					//RangeQuery的下界
					Term begin=new Term("bookname","0000001");
					//RangeQuery的上界
					Term end=new Term("bookname","0000007");
					
					RangeQuery query=new RangeQuery(begin,end,false); 
					System.out.println(query.toString());
					Hits hits=searcher.search(query);
					
					for(int i=0;i<hits.length();i++)
						System.out.println(hits.doc(i)); 
			}catch(IOException ex){
				ex.printStackTrace();
			}
			
		}
		
		//前缀搜索PrefixQuery
		private static void prefixQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),false);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document(); 
				Document doc3=new Document();					
				Document doc4=new Document(); 
				Document doc5=new Document();					
				Document doc6=new Document(); 
				Document doc7=new Document();
				Document doc8=new Document();
				
				Field field1=new Field("bookname","钢铁是怎样炼成的",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("bookname","英雄儿女",Field.Store.YES,Field.Index.TOKENIZED);
				Field field3=new Field("bookname","篱笆女人和狗",Field.Store.YES,Field.Index.TOKENIZED);
				Field field4=new Field("bookname","女人是水做的",Field.Store.YES,Field.Index.TOKENIZED);
				Field field5=new Field("bookname","我的兄弟和女儿",Field.Store.YES,Field.Index.TOKENIZED);
				Field field6=new Field("bookname","白毛女",Field.Store.YES,Field.Index.TOKENIZED);
				Field field7=new Field("bookname","钢的世界",Field.Store.YES,Field.Index.TOKENIZED);
				Field field8=new Field("bookname","钢铁战士",Field.Store.YES,Field.Index.TOKENIZED);
	
				doc1.add(field1);
				doc2.add(field2);
				doc3.add(field3);
				doc4.add(field4);
				doc5.add(field5);
				doc6.add(field6);
				doc7.add(field7);
				doc8.add(field8);
				
				writer.addDocument(doc1);
				writer.addDocument(doc2);
				writer.addDocument(doc3);
				writer.addDocument(doc4);
				writer.addDocument(doc5);
				writer.addDocument(doc6);
				writer.addDocument(doc7);
				writer.addDocument(doc8);
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				Term prefix=new Term("bookname","钢");
				PrefixQuery query=new PrefixQuery(prefix);
				Hits hits=searcher.search(query);
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				System.out.println("==============================END!====================");
			}
			catch(IOException ex){
				ex.printStackTrace();
			}
			
		}
		
		//短语搜索PhraseQuery
		private static void pharseQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document(); 
				Document doc3=new Document();					
				Document doc4=new Document(); 
				Document doc5=new Document();					
				Document doc6=new Document(); 
				Document doc7=new Document();
				Document doc8=new Document();
				
				Field field1=new Field("bookname","钢铁是怎样炼成的",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("bookname","钢 铁 战 士",Field.Store.YES,Field.Index.TOKENIZED);
				Field field3=new Field("bookname","钢和铁是两种金属元素",Field.Store.YES,Field.Index.TOKENIZED);
				Field field4=new Field("bookname","钢要比铁有更多的碳元素",Field.Store.YES,Field.Index.TOKENIZED);
				Field field5=new Field("bookname","钢和铁是两种重要的元素",Field.Store.YES,Field.Index.TOKENIZED);
				Field field6=new Field("bookname","钢铁是两种重要的金属",Field.Store.YES,Field.Index.TOKENIZED); 
				doc1.add(field1);
				doc2.add(field2);
				doc3.add(field3);
				doc4.add(field4);
				doc5.add(field5);
				doc6.add(field6); 
				
				writer.addDocument(doc1);
				writer.addDocument(doc2);
				writer.addDocument(doc3);
				writer.addDocument(doc4);
				writer.addDocument(doc5);
				writer.addDocument(doc6); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				PhraseQuery query=new PhraseQuery(); 
				query.add(new Term("bookname","钢")); 
				query.add(new Term("bookname","铁"));
				Hits hits=searcher.search(query);
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				System.out.println("==============================END!====================");
			}
			catch(IOException ex){
				ex.printStackTrace();
			}
		}

		//多短语搜索MultiPhraseQuery
		private static void multiPharseQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document(); 
				Document doc3=new Document();					
				Document doc4=new Document(); 
				Document doc5=new Document();					
				Document doc6=new Document(); 
				Document doc7=new Document();
				Document doc8=new Document();
				
				Field field1=new Field("bookname","钢铁是怎样炼成的",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("bookname","钢 铁 战 士",Field.Store.YES,Field.Index.TOKENIZED);
				Field field3=new Field("bookname","钢和铁是两种金属元素",Field.Store.YES,Field.Index.TOKENIZED);
				Field field4=new Field("bookname","钢要比铁有更多的碳元素",Field.Store.YES,Field.Index.TOKENIZED);
				Field field5=new Field("bookname","钢和铁是两种重要的元素",Field.Store.YES,Field.Index.TOKENIZED);
				Field field6=new Field("bookname","钢铁是两种重要的金属",Field.Store.YES,Field.Index.TOKENIZED); 
				doc1.add(field1);
				doc2.add(field2);
				doc3.add(field3);
				doc4.add(field4);
				doc5.add(field5);
				doc6.add(field6); 
				
				writer.addDocument(doc1);
				writer.addDocument(doc2);
				writer.addDocument(doc3);
				writer.addDocument(doc4);
				writer.addDocument(doc5);
				writer.addDocument(doc6); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				
				MultiPhraseQuery query=new MultiPhraseQuery(); 
				//加入要查找的短语的前缀
				query.add(new Term[] {new Term("bookname","钢"),new Term("bookname","和")}); 
				//构建3个Term，作为短语的后缀
				Term term1=new Term("bookname","铁");
				//向Query中加入所有的后缀，与前缀一起，它们将组成3个短语
				query.add(new Term[] {term1});
				
				Hits hits=searcher.search(query);
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				System.out.println("==============================END!===================="); 
			}
			catch(IOException ex) {
				ex.printStackTrace();
			}
			
		}

		//模糊搜索FuzzyQuery
		private static void fuzzyQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document(); 
				Document doc3=new Document();					
				Document doc4=new Document(); 
				Document doc5=new Document();					
				Document doc6=new Document();  
				
				Field field1=new Field("content","word",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("content","work",Field.Store.YES,Field.Index.TOKENIZED);
				Field field3=new Field("content","world",Field.Store.YES,Field.Index.TOKENIZED);
				Field field4=new Field("content","seed",Field.Store.YES,Field.Index.TOKENIZED);
				Field field5=new Field("content","sword",Field.Store.YES,Field.Index.TOKENIZED);
				Field field6=new Field("content","ford",Field.Store.YES,Field.Index.TOKENIZED);
				
				doc1.add(field1);
				doc2.add(field2);
				doc3.add(field3);
				doc4.add(field4);
				doc5.add(field5);
				doc6.add(field6); 
				
				writer.addDocument(doc1);
				writer.addDocument(doc2);
				writer.addDocument(doc3);
				writer.addDocument(doc4);
				writer.addDocument(doc5);
				writer.addDocument(doc6); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
			
				Term term=new Term("content","work");
				
//				FuzzyQuery query=new FuzzyQuery(term);
				FuzzyQuery query=new FuzzyQuery(term,0.5f);//相似度
				Hits hits=searcher.search(query);
				
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
				System.out.println("==============================END!===================="); 
			}
			catch(IOException ex) {
				ex.printStackTrace();
			}  
		}
	
		//通配符搜索WildcardQuery
		private static void wildcardQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document(); 
				Document doc3=new Document();					
				Document doc4=new Document(); 
				Document doc5=new Document();					
				Document doc6=new Document();  
				
				Field field1=new Field("content","word",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("content","work",Field.Store.YES,Field.Index.TOKENIZED);
				Field field3=new Field("content","world",Field.Store.YES,Field.Index.TOKENIZED);
				Field field4=new Field("content","seed",Field.Store.YES,Field.Index.TOKENIZED);
				Field field5=new Field("content","sword",Field.Store.YES,Field.Index.TOKENIZED);
				Field field6=new Field("content","ford",Field.Store.YES,Field.Index.TOKENIZED);
				
				doc1.add(field1);
				doc2.add(field2);
				doc3.add(field3);
				doc4.add(field4);
				doc5.add(field5);
				doc6.add(field6); 
				
				writer.addDocument(doc1);
				writer.addDocument(doc2);
				writer.addDocument(doc3);
				writer.addDocument(doc4);
				writer.addDocument(doc5);
				writer.addDocument(doc6); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				
				WildcardQuery query=new WildcardQuery(new Term("content","?o*"));
				
				Hits hits=searcher.search(query);
				
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
				System.out.println("==============================END!===================="); 
				
			}
			catch(IOException ex){
				ex.printStackTrace();
				
			} 
		}
	
		//跨度搜索SpanTermQuery
		private static void spanQuery_SpanTermQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document(); 
				Document doc3=new Document();		 
				
				Field field1=new Field("content","Last night David gave him very beautiful clothes",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("content","Last night Mary gave him very poor clothes",Field.Store.YES,Field.Index.TOKENIZED);
				Field field3=new Field("content","Last night Candy gave him very beautiful shoes",Field.Store.YES,Field.Index.TOKENIZED);
			 
				doc1.add(field1);
				doc2.add(field2);
				doc3.add(field3);
				 
				writer.addDocument(doc1);
				writer.addDocument(doc2);
				writer.addDocument(doc3); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				 
				SpanTermQuery query=new SpanTermQuery(new Term("content","david"));

				
				Hits hits=searcher.search(query);
				
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
				System.out.println("==============================END!===================="); 
				
				
			}
			catch(IOException ex) {
				ex.printStackTrace();
				
			}
			
		}

		//SpanFirstQuery
		private static void spanQuery_SpanFirstQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document(); 
				Document doc3=new Document();		 
				
				Field field1=new Field("content","Last night David gave him very beautiful clothes",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("content","Last night Mary gave him very poor clothes",Field.Store.YES,Field.Index.TOKENIZED);
				Field field3=new Field("content","Last night Candy gave him very beautiful shoes",Field.Store.YES,Field.Index.TOKENIZED);
			 
				doc1.add(field1);
				doc2.add(field2);
				doc3.add(field3);
				 
				writer.addDocument(doc1);
				writer.addDocument(doc2);
				writer.addDocument(doc3); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				 
				SpanTermQuery people=new SpanTermQuery(new Term("content","mary"));

				System.out.println("Span值设为3");
				SpanFirstQuery query=new SpanFirstQuery(people,3); 
				Hits hits=searcher.search(query); 
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
				
				System.out.println("Span值设为2");
				query=new SpanFirstQuery(people,2); 
				hits=searcher.search(query); 
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
				System.out.println("==============================END!===================="); 
				
				
			}
			catch(IOException ex) {
				ex.printStackTrace(); 
			}
		}

		//SpanNearQuery
		private static void spanQuery_SpanNearQuery_1() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document(); 
				Document doc3=new Document();		 
				
				Field field1=new Field("content","Last night David gave him very beautiful clothes",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("content","Last night Mary gave him very poor clothes",Field.Store.YES,Field.Index.TOKENIZED);
				Field field3=new Field("content","Last night Candy gave him very beautiful shoes",Field.Store.YES,Field.Index.TOKENIZED);
			 
				doc1.add(field1);
				doc2.add(field2);
				doc3.add(field3);
				 
				writer.addDocument(doc1);
				writer.addDocument(doc2);
				writer.addDocument(doc3); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				 
				SpanTermQuery people=new SpanTermQuery(new Term("content","mary"));
				SpanTermQuery how=new SpanTermQuery(new Term("content","poor"));

				System.out.println("设置slop值为3");
				SpanNearQuery  query=new SpanNearQuery(new SpanQuery[] {people,how},3,false); 
				Hits hits=searcher.search(query); 
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
				
				System.out.println("设置slop值为2");
				query=new SpanNearQuery(new SpanQuery[] {people,how},2,false); 
				hits=searcher.search(query); 
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
				System.out.println("==============================END!===================="); 
				
				
			}
			catch(IOException ex) {
				ex.printStackTrace(); 
			}			
		}

		//SpanNearQuery
		private static void spanQuery_SpanNearQuery_2() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document();   
				
				Field field1=new Field("content","aa bb cc dd ee ff gg hh ii ll jj kk",Field.Store.YES,Field.Index.TOKENIZED);
		 	 
				doc1.add(field1); 
				 
				writer.addDocument(doc1);
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
	
				SpanTermQuery spanTermQuery1=new SpanTermQuery(new Term("content","aa"));
				SpanTermQuery spanTermQuery2=new SpanTermQuery(new Term("content","cc"));
				SpanTermQuery spanTermQuery3=new SpanTermQuery(new Term("content","gg"));
				SpanTermQuery spanTermQuery4=new SpanTermQuery(new Term("content","kk"));
	 
				SpanNearQuery  query1=new SpanNearQuery(new SpanQuery[] {spanTermQuery1,spanTermQuery2},1,false);
				SpanNearQuery  query2=new SpanNearQuery(new SpanQuery[] {spanTermQuery3,spanTermQuery4},3,false);
				
				SpanNearQuery  query=new SpanNearQuery(new SpanQuery[] {query1,query2},3,false);
				
				Hits hits=searcher.search(query); 
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
			 
				System.out.println("==============================END!===================="); 
				
				
			}
			catch(IOException ex) {
				ex.printStackTrace(); 
			}			
		}
		//SpanOrQuery
		private static void spanQuery_SpanOrQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document();   
				
				Field field1=new Field("content","aa bb cc dd ee",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("content","ff gg hh ii jj kk",Field.Store.YES,Field.Index.TOKENIZED);
			  
				doc1.add(field1);
				doc2.add(field2); 
				 
				writer.addDocument(doc1);
				writer.addDocument(doc2); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				 
				SpanTermQuery s1=new SpanTermQuery(new Term("content","aa"));
				SpanTermQuery s2=new SpanTermQuery(new Term("content","bb"));
				SpanTermQuery s3=new SpanTermQuery(new Term("content","ff"));
				SpanTermQuery s4=new SpanTermQuery(new Term("content","jj"));

				SpanNearQuery query1=new SpanNearQuery(new SpanQuery[]{s1,s2},1,false);
				SpanNearQuery query2=new SpanNearQuery(new SpanQuery[]{s3,s4},3,false);
				
				Hits hits=searcher.search(query1); 
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				
				SpanOrQuery query=new SpanOrQuery(new SpanQuery[] {query1,query2});

				hits=searcher.search(query); 
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				 
				System.out.println("==============================END!===================="); 
				
				
			}
			catch(IOException ex) {
				ex.printStackTrace(); 
			}	
		}
 
		private static void spanQuery_SpanNotQuery() {
			try {
				System.out.println("==============================BEGIN!====================");
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.setUseCompoundFile(false);
				
				Document doc1=new Document(); 
				Document doc2=new Document();   
				
				Field field1=new Field("content","aa bb cc dd ee",Field.Store.YES,Field.Index.TOKENIZED);
				Field field2=new Field("content","ff gg hh ii jj kk",Field.Store.YES,Field.Index.TOKENIZED);
			  
				doc1.add(field1);
				doc2.add(field2); 
				 
				writer.addDocument(doc1);
				writer.addDocument(doc2); 
				
				writer.close();
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				 
				SpanTermQuery s1=new SpanTermQuery(new Term("content","aa"));
				SpanTermQuery s2=new SpanTermQuery(new Term("content","bb"));
				SpanNearQuery query1=new SpanNearQuery(new SpanQuery[]{s1,s2},1,false);
					
				SpanTermQuery s3=new SpanTermQuery(new Term("content","ff"));
				SpanTermQuery s4=new SpanTermQuery(new Term("content","jj"));
				SpanNearQuery query2=new SpanNearQuery(new SpanQuery[]{s3,s4},3,false);
				
				SpanOrQuery query=new SpanOrQuery(new SpanQuery[] {query1,query2});
				 
			 	Hits hits=searcher.search(query); 
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i));
				 
				System.out.println("==============================END!===================="); 
				
				
			}
			catch(IOException ex) {
				ex.printStackTrace(); 
			}		
		}
 
		private static void spanQuery_RegexQuery() {
//			try { 
//				System.out.println("==============================BEGIN!====================");
//				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
//				writer.setUseCompoundFile(false);
//				
//				Document doc1=new Document(); 
//				Document doc2=new Document();   
//				Document doc3=new Document();   
//				
//				Field field1=new Field("url","http://www.baidu.com",Field.Store.YES,Field.Index.UN_TOKENIZED);
//				Field field2=new Field("url","http://www.google.com",Field.Store.YES,Field.Index.UN_TOKENIZED);
//				Field field3=new Field("url","http://www.taobao.com",Field.Store.YES,Field.Index.UN_TOKENIZED);
//			  
//				doc1.add(field1);
//				doc2.add(field2);
//				doc3.add(field3);
//				 
//				writer.addDocument(doc1);
//				writer.addDocument(doc2); 
//				writer.addDocument(doc3);   
//				
//				writer.close();
//				
//				
//				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
//				
//				String regex="http://[a-z] {1,3}\\.abc\\.com/.*";
//				 
//				Term term=new Term("url",regex);
//				
//				RegexQuery query=new RegexQuery(term);
//				
//			 	Hits hits=searcher.search(query); 
//				for(int i=0;i<hits.length();i++)
//					System.out.println(hits.doc(i));
//				 
//				System.out.println("==============================END!===================="); 
//				
//			}
//			catch(IOException ex) {
//				ex.printStackTrace();
//				
//			}
			
		}

		//通过QueryParse转换用户关键字
		private static void queryParse(){
			try {
				Document doc=new Document();
				Field bookNo=new Field("bookNo","FB309663100",Field.Store.YES,Field.Index.UN_TOKENIZED);
				Field bookName=new Field("bookName","《钢铁是怎样炼成的》",Field.Store.YES,Field.Index.TOKENIZED);
				Field author=new Field("author","薛拾军",Field.Store.YES,Field.Index.TOKENIZED);
				Field publishdate=new Field("publishdate","2012-5-12",Field.Store.YES,Field.Index.TOKENIZED);
				Field bookabstract=new Field("bookabstract","钢铁是怎样炼成的，火中烤！",Field.Store.YES,Field.Index.TOKENIZED);
				Field price=new Field("price","25.00",Field.Store.YES,Field.Index.TOKENIZED);				
				
				doc.add(bookNo);
				doc.add(bookName);
				doc.add(author);
				doc.add(publishdate);
				doc.add(bookabstract);
				doc.add(price);
				
				IndexWriter writer=new IndexWriter(INDEX_STORE_PATH,new StandardAnalyzer(),true);
				writer.addDocument(doc);
				
				IndexSearcher searcher=new IndexSearcher(INDEX_STORE_PATH);
				
				String queryString1="钢 publishdate:2012-5-12";
				String queryString2="战";
				String queryString3="price:25:00";
				String queryString4="publishdate:2012-5-12";
				
				
				QueryParser parser=new QueryParser("bookname",new StandardAnalyzer());
				parser.setDefaultOperator(QueryParser.AND_OPERATOR);
				System.out.println(queryString1);
				Query query=parser.parse(queryString1); 
				System.out.println(query.toString()); 
				Hits hits=searcher.search(query);
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i)); 
				System.out.println("-------------------");

				System.out.println(queryString2);
				query=parser.parse(queryString2); 
				System.out.println(query.toString()); 
				hits=searcher.search(query);
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i)); 
				System.out.println("-------------------");
				System.out.println(queryString3);
				query=parser.parse(queryString3); 
				System.out.println(query.toString()); 
				hits=searcher.search(query);
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i)); 
				System.out.println("-------------------");
						
				System.out.println(queryString4);
				query=parser.parse(queryString4); 
				System.out.println(query.toString()); 
				hits=searcher.search(query);
				for(int i=0;i<hits.length();i++)
					System.out.println(hits.doc(i)); 
				System.out.println("-------------------"); 
				
			} 
			catch(IOException ex){
				ex.printStackTrace();
			}
			catch(ParseException ex){
				 ex.printStackTrace();
			}
			
		}

		//MultiSearcher在多个索引上搜索
		private static void multiSearcher() {
			try {
				
				IndexWriter writer1=new IndexWriter(INDEX_STORE_PATH1,new StandardAnalyzer(),true);
				writer1.setUseCompoundFile(false);
				
				Document doc1=new Document();
				Document doc2=new Document();
				Document doc3=new Document();
				
 				Field field1=new Field("bookname","钢铁是怎样炼成的",Field.Store.YES,Field.Index.TOKENIZED);
				Field field11=new Field("price","20.50",Field.Store.YES,Field.Index.UN_TOKENIZED);				
				
 				Field field2=new Field("bookname","钢铁战士",Field.Store.YES,Field.Index.TOKENIZED);
				Field field21=new Field("price","18.4",Field.Store.YES,Field.Index.UN_TOKENIZED);		
				
 				Field field3=new Field("bookname","钢和铁是两种金属元素",Field.Store.YES,Field.Index.TOKENIZED);
				Field field31=new Field("price","7.6",Field.Store.YES,Field.Index.UN_TOKENIZED);
				
				doc1.add(field1);
				doc1.add(field11);
				
				doc2.add(field2);
				doc2.add(field21);
				
				doc3.add(field3);
				doc3.add(field31);
				
				writer1.addDocument(doc1);
				writer1.addDocument(doc2);
				writer1.addDocument(doc3);
				writer1.close();
				
				IndexWriter writer2=new IndexWriter(INDEX_STORE_PATH2,new StandardAnalyzer(),true);
				writer2.setUseCompoundFile(false);
				
				Document doc4=new Document();
				Document doc5=new Document();
				Document doc6=new Document();
				
 				Field field4=new Field("bookname","钢要比铁有更多的碳元素",Field.Store.YES,Field.Index.TOKENIZED);
				Field field41=new Field("price","22",Field.Store.YES,Field.Index.UN_TOKENIZED);				
				
 				Field field5=new Field("bookname","铁和钢是两种重要的金属",Field.Store.YES,Field.Index.TOKENIZED);
				Field field51=new Field("price","15.9",Field.Store.YES,Field.Index.UN_TOKENIZED);		
				
 				Field field6=new Field("bookname","铁钢是两种重要的金属",Field.Store.YES,Field.Index.TOKENIZED);
				Field field61=new Field("price","19.0",Field.Store.YES,Field.Index.UN_TOKENIZED);
				
				doc4.add(field4);
				doc4.add(field41);
				
				doc5.add(field5);
				doc5.add(field51);
				
				doc6.add(field6);
				doc6.add(field61);
				
				writer2.addDocument(doc4);
				writer2.addDocument(doc5);
				writer2.addDocument(doc6);
				writer2.close();

				
				//创建多域搜索 
				String [] queries= {"钢","[10 TO 20]"}; 
				
				String [] fields = {"bookname","price"};
				
				//查询子句间的关系
				BooleanClause.Occur [] clauses= {BooleanClause.Occur.MUST,BooleanClause.Occur.MUST};

				Query query=MultiFieldQueryParser.parse(queries,fields,clauses,new StandardAnalyzer());
				
				System.out.println(query.toString());
				
				IndexSearcher seacher1=new IndexSearcher(INDEX_STORE_PATH1);
				IndexSearcher seacher2=new IndexSearcher(INDEX_STORE_PATH2);
				IndexSearcher [] searchers= {seacher1,seacher2};
				
				//MultiSearcher在多索引上搜索
				MultiSearcher searcher=new MultiSearcher(searchers);
				
				Hits hits=searcher.search(query);
				for(int i=0;i<hits.length();i++){
					System.out.println(hits.doc(i));
				}
			} 
			catch(IOException ex){
				ex.printStackTrace();
			}
			catch(ParseException ex){
				 ex.printStackTrace();
			}
		} 
	
		
	}

	
	/**
	 * ********************************************
	 ******************多线程搜索*********************
	 ********************************************** 
	 * */
	private static class ParallelMutilSearcherClass{
		//设定存放索引的根目录
		private static String INDEX_STORE_PATH_BASE="E:\\Index\\SubIndex";
		//设定总共的索引目录数量
		private static int INDEX_DIR_NUMBER=100;
		
		public static void parallelMutilSearcher() {
			try {
					System.out.println("====================BEGIN!==============");
					
					for(int i=0;i<INDEX_DIR_NUMBER;i++) {
						IndexWriter writer =new IndexWriter(INDEX_STORE_PATH_BASE+i,new StandardAnalyzer(),true);
						Document doc=new Document();
						Field field =new Field("bookname","薛拾军"+i,Field.Store.YES,Field.Index.TOKENIZED);
						doc.add(field);
						writer.addDocument(doc);
						writer.close();//关闭索引器
					}
					 
//					//使用IndexReader来读取索引 
					System.out.println("======索引文档列表======"); 
					for(int i=0;i<INDEX_DIR_NUMBER;i++)
					{ 
						IndexReader reader=IndexReader.open(INDEX_STORE_PATH_BASE+i);
						System.out.println("版本："+reader.getVersion());//当前索引版本信息
						System.out.println("索引内文档数量："+reader.numDocs());//当前索引的文档数量
						for(int j=0;j<reader.numDocs();j++) {
							System.out.println(i+"_"+reader.document(j));//显示索引内所有的Document
						}
						reader.close();
					}  
					
					IndexSearcher [] searchers=new IndexSearcher[INDEX_DIR_NUMBER];
					for(int i=0;i<INDEX_DIR_NUMBER;i++) {
						searchers[i]=new IndexSearcher(INDEX_STORE_PATH_BASE+i);
					}
					
				
					
					
					
					Term term=new Term("bookname","钢");
					TermQuery query=new TermQuery(term);
					/**使用MultiSearcher搜索  */
					multiSearch(searchers,query);
					/**使用ParallMultiSearcher搜索*/
					parallelSearch(searchers,query);
					System.out.println("====================END!==============");	
					
					
			} 
			catch(IOException ex){
				ex.printStackTrace();
			} 
			
		} 
	 
		/**使用MultiSearcher搜索  */
		public static void multiSearch(IndexSearcher[]searchers,Query query) throws IOException {
			MultiSearcher msearcher=new MultiSearcher(searchers);
			long start=System.currentTimeMillis();
			Hits hits=msearcher.search(query);
			long end=System.currentTimeMillis();
			//计算搜索用时
			System.out.println("使用ParallelMultiSearcher用时："+(end-start)+"毫秒"); 
		}
		/**使用ParallMultiSearcher搜索*/
		public static void parallelSearch(IndexSearcher[]searchers,Query query) throws IOException {
			ParallelMultiSearcher searcher=new ParallelMultiSearcher(searchers);
			long start=System.currentTimeMillis();
			Hits hits=searcher.search(query);
			long end=System.currentTimeMillis();
			//计算搜索用时
			System.out.println("使用MultiSearcher用时："+(end-start)+"毫秒"); 
		}
	
		
	}		
		
	
} 
