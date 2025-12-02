
# Cards View

- Product & Services
    - matomo-app                        # on
    - Syncthing                         # on
    - Cloud_Dashboard                   # dev
    - mailserver                        # dev
    - Web_Shell_Terminal                # dev
    - Agentic_Dashboard                 # dev


---

- Management
    - Cloud Providers
        - OCloud-Management                 # on
        - Gcloud_Management                 # on

    - SSH VMs
        - SSH-VM-Oracle_Services_Serv       # on
        - SSH-VM-Oracle_Web_Server_1        # on
        - SSH-VM-Oracle_Flex_ARM_Server     # dev
        - SSH-VM-GCloud_microe2Linux_1      # dev

- Infra Services
    - NPMs
        - NPM-VM-Oracle_Services_Serv       # on
        - NPM-VM-Oracle_Web_Server_1        # on
        - NPM-VM-Oracle_Flex_ARM_Server     # dev
        - NPM-VM-Gcloud                     # dev
    - Data Bases
        - matomo-db                         # on
        - mail-db                           # dev
        - n8n-AI_db
    - Others
        - n8n-AI-server                     # dev
        - Flask-server                      #





# Tree View

## Infra as Service VPS IaaS (Raw)
- Google Cloud
    - Gcloud_Management                     #
    - SSH-VM-GCloud_microe2Linux_1          #
        - NPM-VM-Gcloud
        - mailserver                        #
        - mail-db                           #
        - Web_Shell_Terminal                #

- Oracle Cloud
    - OCloud-Management                     #
    - SSH-VM-Oracle_Web_Server_1            #
        - NPM-VM-Oracle_Web_Server_1        #
        - n8n-server                        #
            - Infra                         #
        - Syncthing                         #
        - Flask-server                      #
            - Cloud_Dashboard.py            #
            - Cloud_Dashboard-db            #

    - SSH-VM-Oracle_Services_Serv           #
        - NPM-VM-Oracle_Services_Serv       #
        - matomo-app                        #
        - matomo-db                         #
        - Cloud_Dashboard-db                #

    - SSH-VM-Oracle_Flex_ARM_Server         #
        - NPM-VM-Oracle_Flex_ARM_Server     #
        - n8n-server                        #
            - AI Agentic                    #

## Pay per use GPU VRAM and RAM
### WebAPP
- Python(Flask/Django)
    - Streamlit

### AI
- PaaS
    - Hugging Face Spaces
    - Koyeb/Railway/Render
- FaaS
    - Google Cloud Functions,
    - Modal,
    - Beam/RunPod
- MaaS
    - Hugging Face API,
    - Groq,
    - Together AI/OpenRouter
- AaaS
    - E2B,
    - Relevance AI




# Architeture

## Infra_Servers

(add here mermaid code)


## AI_Servers

(add here mermaid code)

