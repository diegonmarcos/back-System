import type { Metadata } from 'next'

export const viewport = {
  themeColor: '#2563eb',
  width: 'device-width',
  initialScale: 1,
}

export const metadata: Metadata = {
  metadataBase: new URL('https://jsonvision.dev'),
  title: {
    default: 'JSON Vision - Visualize & Extract Paths',
    template: '%s | JSON Vision',
  },
  description: 'A powerful JSON visualization tool with tree and graph views, path extraction, JSONPath queries, and real-time validation. Built with Next.js.',
  keywords: ['JSON', 'visualizer', 'JSON viewer', 'JSON formatter', 'JSON path', 'JSONPath', 'tree view', 'graph view', 'JSON tool'],
  authors: [{ name: 'Hardik Joshi', url: 'https://github.com/ReachOutToHardik' }],
  creator: 'Hardik Joshi',
  icons: {
    icon: [
      { url: '/favicon.svg', type: 'image/svg+xml' },
      { url: '/favicon.ico', sizes: '32x32' },
    ],
    shortcut: '/favicon.ico',
    apple: [
      { url: '/apple-icon.png', sizes: '180x180', type: 'image/png' },
    ],
  },
  manifest: '/manifest.json',
  openGraph: {
    type: 'website',
    locale: 'en_US',
    url: 'https://jsonvision.dev',
    title: 'JSON Vision - Visualize & Extract Paths',
    description: 'A powerful JSON visualization tool with tree and graph views, path extraction, and real-time validation',
    siteName: 'JSON Vision',
  },
  twitter: {
    card: 'summary_large_image',
    title: 'JSON Vision',
    description: 'Powerful JSON visualization tool with multiple view modes',
    creator: '@yourhandle',
  },
  robots: {
    index: true,
    follow: true,
    googleBot: {
      index: true,
      follow: true,
      'max-video-preview': -1,
      'max-image-preview': 'large',
      'max-snippet': -1,
    },
  },
}
