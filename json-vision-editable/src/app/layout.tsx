import type { Metadata } from 'next'
import { Inter } from 'next/font/google'
import './globals.css'

const inter = Inter({ subsets: ['latin'] })

export const metadata: Metadata = {
  metadataBase: new URL('https://jsonvision.vercel.app'),
  title: {
    default: 'JSON Vision - Visualize & Extract Paths',
    template: '%s | JSON Vision',
  },
  description: 'A powerful JSON visualization tool with tree and graph views, path extraction, JSONPath queries, and real-time validation. Built with Next.js.',
  keywords: ['JSON', 'visualizer', 'JSON viewer', 'JSON formatter', 'JSON path', 'JSONPath', 'tree view', 'graph view', 'JSON tool', 'developer tools'],
  authors: [{ name: 'Hardik Joshi', url: 'https://github.com/ReachOutToHardik' }],
  creator: 'Hardik Joshi',
  icons: {
    icon: [
      { url: '/favicon.svg', type: 'image/svg+xml' },
      { url: '/favicon.ico', sizes: '32x32' },
    ],
    shortcut: '/favicon.ico',
    apple: { url: '/apple-icon.png', sizes: '180x180', type: 'image/png' },
  },
  manifest: '/manifest.json',
  openGraph: {
    type: 'website',
    locale: 'en_US',
    url: 'https://jsonvision.vercel.app',
    title: 'JSON Vision - Visualize & Extract Paths',
    description: 'A powerful JSON visualization tool with tree and graph views, path extraction, and real-time validation',
    siteName: 'JSON Vision',
  },
  twitter: {
    card: 'summary_large_image',
    title: 'JSON Vision',
    description: 'Powerful JSON visualization tool with multiple view modes',
  },
  robots: {
    index: true,
    follow: true,
  },
}

export default function RootLayout({
  children,
}: {
  children: React.ReactNode
}) {
  return (
    <html lang="en">
      <body className={inter.className}>{children}</body>
    </html>
  )
}
