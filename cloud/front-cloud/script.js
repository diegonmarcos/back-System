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
            'proxy': '/proxy',
            'firewall': '/firewall',
            'mail': '/mail',
            'sync': '/sync',
            'drive': '/drive',
            'vps-oracle': '/vps/oracle',
            'analytics': '/analytics',
            'vps-local': '/vps/local',
            'terminal': '/terminal',
            'dashboard': '/ops/dashboard'
        };

        const url = serviceUrls[service];
        if (url) {
            console.log(`Navigating to ${service}: ${url}`);
            // window.location.href = url;

            // For now, show a notification
            showNotification(`Opening ${service.replace('-', ' ').toUpperCase()}...`);
        }
    }

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
