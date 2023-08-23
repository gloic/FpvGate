# import os
# os.environ["OPENAI_API_BASE"] = "http://127.0.0.1:5001/v1"

import langchain
from langchain import PromptTemplate, LLMChain
from langchain.document_loaders import MWDumpLoader
from langchain.embeddings.openai import OpenAIEmbeddings
from langchain.llms import TextGen
# create the open-source embedding function
from langchain.embeddings.sentence_transformer import SentenceTransformerEmbeddings
from langchain.text_splitter import CharacterTextSplitter
from langchain.text_splitter import CharacterTextSplitter
from langchain.vectorstores import Chroma


langchain.debug = True

model_url = "http://localhost:5000"

def chain():
    def generate(question):
        print(llm_chain.run(question))

    template = """
    Tu es un assistant au service des utilisateurs.
    
    ### Instruction: {question}
    
    ### Response: """

    prompt = PromptTemplate(template=template, input_variables=["question"])
    llm = TextGen(model_url=model_url)

    llm_chain = LLMChain(prompt=prompt, llm=llm)
    question = "Bonjour monsieur, comment ça va ?"

    generate(question)


def wiki():
    loader = MWDumpLoader(
        file_path = "Wikefluid-20230823142901.xml",
        encoding="utf8",
        #namespaces = [0,2,3] Optional list to load only specific namespaces. Loads all namespaces by default.
    )
    documents = loader.load()
    print(f"You have {len(documents)} document(s) in your data ")

    wiki = ''
    for doc in documents:
        page_separator = "<!!!>"
        wiki += doc.page_content + page_separator


    # print(wiki)
    with open("wiki.txt", "w", encoding="utf-8") as file:
        file.write(wiki)

    # def split():
    #     text_splitter = CharacterTextSplitter(chunk_size=30, chunk_overlap=0)
    #     return text_splitter.split_documents(documents)
    # docs = split()
    # openai_api_key="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"
    # embeddings = OpenAIEmbeddings(openai_api_base="http://127.0.0.1:5001/v1", openai_api_key="osef")
    # text = "This is a test query."
    # query_result = embeddings.embed_documents(documents) # cpt


    # db = Chroma.from_documents(docs, embeddings)
    # db = Chroma.from_texts(texte, embedding=embeddings)

    # query = "Que signfie : j'ai retrouvé l'AFD sur la migration des PRM de PDS pour SEI"
    # res = db.similarity_search(query)
    # print(res[0].page_content)
    # print(f"Query result = {query_result}")

# chain()
wiki()


