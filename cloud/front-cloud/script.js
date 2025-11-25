document.addEventListener('DOMContentLoaded', () => {
    const cards = document.querySelectorAll('.card');

    cards.forEach(card => {
        card.addEventListener('mouseenter', (e) => {
            card.style.zIndex = '10';
        });

        card.addEventListener('mouseleave', (e) => {
            card.style.zIndex = '1';
        });

        card.addEventListener('mousemove', (e) => {
            const rect = card.getBoundingClientRect();
            const x = e.clientX - rect.left;
            const y = e.clientY - rect.top;

            const centerX = rect.width / 2;
            const centerY = rect.height / 2;

            const rotateX = (y - centerY) / 10;
            const rotateY = (centerX - x) / 10;

            card.style.transform = `
                translateY(-12px)
                scale(1.02)
                perspective(1000px)
                rotateX(${rotateX}deg)
                rotateY(${rotateY}deg)
            `;
        });

        card.addEventListener('mouseleave', () => {
            card.style.transform = 'translateY(0) scale(1) rotateX(0) rotateY(0)';
        });

        card.addEventListener('click', () => {
            const service = card.dataset.service;
            handleCardClick(service);
        });
    });

    function handleCardClick(service) {
        const serviceUrls = {
            // Active Services
            'proxy': 'http://130.110.251.193:81',           // Nginx Proxy Manager Admin
            'analytics': 'http://130.110.251.193:8080',     // Matomo Direct Access
            'firewall': '../vps_oracle/spec.md',            // Infrastructure Spec

            // Active VPS
            'vps-oracle-console': 'https://cloud.oracle.com/',      // Oracle Cloud Console
            'vps-gcloud-console': 'https://console.cloud.google.com/', // Google Cloud Console

            // Active VMs
            'vm-ubuntu1': 'ssh://ubuntu@130.110.251.193',   // SSH to Ubuntu1 VM (Oracle)
            'vm-arch1': 'ssh://user@pending',               // SSH to Arch1 VM (GCloud) - placeholder

            // Under Development
            'mail': '../mail/index.html',
            'sync': '../sync/index.html',
            'drive': '../drive/index.html',
            'vps-local': '../vps_google/index.html',
            'terminal': '../1.ops/index.html',
            'dashboard': '../0.spec/index.html'
        };

        const url = serviceUrls[service];
        if (url) {
            console.log(`Navigating to ${service}: ${url}`);

            // Handle SSH protocol
            if (url.startsWith('ssh://')) {
                handleSSH(url);
            }
            // Open external URLs in new tab
            else if (url.startsWith('http')) {
                window.open(url, '_blank');
            }
            // Navigate to local files
            else {
                window.location.href = url;
            }
        }
    }

    function handleSSH(sshUrl) {
        // Extract username and host from ssh://ubuntu@130.110.251.193
        const match = sshUrl.match(/ssh:\/\/(.+)@(.+)/);
        if (!match) return;

        const username = match[1];
        const host = match[2];

        // Check if this is a pending VM
        if (host === 'pending' || host.includes('pending')) {
            showNotification('This VM is not yet configured. IP address pending.');
            return;
        }

        const sshCommand = `ssh -i ~/.ssh/matomo_key ${username}@${host}`;

        // Show modal with SSH command and options
        showSSHModal(sshCommand, host);
    }

    function showSSHModal(sshCommand, host) {
        // Create modal overlay
        const modal = document.createElement('div');
        modal.className = 'ssh-modal-overlay';
        modal.innerHTML = `
            <div class="ssh-modal">
                <h3>SSH Connection to ${host}</h3>
                <div class="ssh-command">
                    <code>${sshCommand}</code>
                    <button class="copy-btn" onclick="copyToClipboard('${sshCommand}')">Copy</button>
                </div>
                <p class="ssh-instruction">Choose how to connect:</p>
                <div class="ssh-options">
                    <button class="ssh-option-btn" onclick="openTerminalProtocol('${sshCommand}')">
                        Open in Terminal
                    </button>
                    <button class="ssh-option-btn" onclick="openVSCode('${sshCommand}')">
                        Open in VS Code
                    </button>
                </div>
                <button class="close-modal-btn" onclick="closeSSHModal()">Close</button>
            </div>
        `;

        document.body.appendChild(modal);

        // Close on overlay click
        modal.addEventListener('click', (e) => {
            if (e.target === modal) {
                closeSSHModal();
            }
        });
    }

    // Global functions for modal buttons
    window.closeSSHModal = function() {
        const modal = document.querySelector('.ssh-modal-overlay');
        if (modal) modal.remove();
    };

    window.copyToClipboard = function(text) {
        navigator.clipboard.writeText(text).then(() => {
            showNotification('SSH command copied to clipboard!');
        });
    };

    window.openTerminalProtocol = function(sshCommand) {
        // Try different terminal protocols based on OS
        const isLinux = /Linux/.test(navigator.userAgent);
        const isMac = /Mac/.test(navigator.userAgent);

        if (isLinux) {
            // Try gnome-terminal, konsole, xterm
            window.location.href = `gnome-terminal://execute/${encodeURIComponent(sshCommand)}`;
        } else if (isMac) {
            // macOS Terminal
            window.location.href = `terminal://execute/${encodeURIComponent(sshCommand)}`;
        } else {
            // Fallback: copy to clipboard
            copyToClipboard(sshCommand);
            showNotification('Command copied! Paste it in your terminal.');
        }
        closeSSHModal();
    };

    window.openVSCode = function(sshCommand) {
        // Extract host for VS Code remote SSH
        const match = sshCommand.match(/(.+)@([^\s]+)/);
        if (match) {
            const username = match[1].split(' ').pop();
            const host = match[2];
            // VS Code Remote SSH extension URL
            window.open(`vscode://vscode-remote/ssh-remote+${username}@${host}/home/${username}`, '_blank');
        }
        closeSSHModal();
    };

    function showNotification(message) {
        const notification = document.createElement('div');
        notification.textContent = message;
        notification.style.cssText = `
            position: fixed;
            top: 20px;
            right: 20px;
            background: linear-gradient(135deg, #4a9eff, #8b5cf6);
            color: white;
            padding: 1rem 1.5rem;
            border-radius: 8px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.3);
            z-index: 1000;
            animation: slideIn 0.3s ease-out;
            font-weight: 500;
        `;

        document.body.appendChild(notification);

        setTimeout(() => {
            notification.style.animation = 'slideOut 0.3s ease-out';
            setTimeout(() => notification.remove(), 300);
        }, 2000);
    }

    const style = document.createElement('style');
    style.textContent = `
        @keyframes slideIn {
            from {
                transform: translateX(400px);
                opacity: 0;
            }
            to {
                transform: translateX(0);
                opacity: 1;
            }
        }

        @keyframes slideOut {
            from {
                transform: translateX(0);
                opacity: 1;
            }
            to {
                transform: translateX(400px);
                opacity: 0;
            }
        }
    `;
    document.head.appendChild(style);

    const statusElements = document.querySelectorAll('.card-status');
    statusElements.forEach(status => {
        setInterval(() => {
            if (Math.random() > 0.95) {
                status.style.animation = 'pulse 0.5s ease-in-out';
                setTimeout(() => {
                    status.style.animation = '';
                }, 500);
            }
        }, 2000);
    });

    const pulseStyle = document.createElement('style');
    pulseStyle.textContent = `
        @keyframes pulse {
            0%, 100% { transform: scale(1); }
            50% { transform: scale(1.05); }
        }
    `;
    document.head.appendChild(pulseStyle);
});
