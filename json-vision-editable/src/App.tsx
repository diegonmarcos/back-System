import React, { useState, useEffect, useRef } from 'react';
import { 
  Copy, 
  Trash2, 
  Minimize2, 
  FileJson, 
  Search, 
  Check, 
  AlertCircle, 
  ChevronRight, 
  ChevronDown, 
  Braces, 
  Download,
  Play,
  Share2,
  Network,
  Move,
  Github,
  Twitter,
  Globe,
  Zap,
  Eye,
  Code2,
  Upload,
  Folder,
  Target,
  Instagram,
  InstagramIcon,
  Linkedin,
  Plus,
  X,
  Save,
  RefreshCw,
  FileText,
  Edit3
} from 'lucide-react';

// --- HOOKS ---

function useDebounce<T>(value: T, delay: number): T {
  const [debouncedValue, setDebouncedValue] = useState(value);

  useEffect(() => {
    const handler = setTimeout(() => {
      setDebouncedValue(value);
    }, delay);

    return () => {
      clearTimeout(handler);
    };
  }, [value, delay]);

  return debouncedValue;
}

// --- UTILS: Graph Layout Logic ---

// Helper to safely update object by path
const setValueByPath = (obj: any, path: string, key: string, value: any): any => {
  const newObj = JSON.parse(JSON.stringify(obj)); // Deep clone
  
  // If path is empty, we are at root
  if (!path) {
    newObj[key] = value;
    return newObj;
  }

  // Parse path: "team.leads[0]" -> ["team", "leads", "0"]
  // Simple regex to split by . or []
  const parts = path.replace(/\]/g, '').split(/[.\[]/);
  
  let current = newObj;
  for (let i = 0; i < parts.length; i++) {
    const part = parts[i];
    if (current[part] === undefined) return obj; // Error path not found
    current = current[part];
  }

  // Now current is the object/array containing the key
  current[key] = value;
  return newObj;
};

// Calculates the size (leaf units) of a node based on its children
const calculateTreeSize = (data: any): number => {
  if (data === null || typeof data !== 'object') return 1;
  const keys = Object.keys(data);
  if (keys.length === 0) return 1;
  let size = 0;
  keys.forEach(key => {
    const value = data[key];
    if (typeof value === 'object' && value !== null) {
      size += calculateTreeSize(value);
    } else {
      size += 1;
    }
  });
  return size;
};

interface GraphNode {
  id: string;
  type: 'array' | 'object';
  path: string;
  x: number;
  y: number;
  data: Record<string, any>;
  label: string;
  totalSize: number;
}

interface GraphEdge {
  from: string;
  to: string;
  label: string;
}

interface GraphResult {
  nodes: GraphNode[];
  edges: GraphEdge[];
  size: number;
}

// Converts JSON to Nodes and Edges with coordinates based on layout mode
const processGraph = (
  data: any, 
  layout: 'vertical' | 'horizontal' = 'vertical',
  path = '', 
  depth = 0, 
  startOffset = 0
): GraphResult => {
  const nodes: GraphNode[] = [];
  const edges: GraphEdge[] = [];
  
  if (typeof data !== 'object' || data === null) {
    return { nodes: [], edges: [], size: 1 };
  }

  const keys = Object.keys(data);
  const isArray = Array.isArray(data);
  const nodeId = path || 'root';
  const myTreeSize = calculateTreeSize(data); 
  
  const V_X_GAP = 500;
  const V_Y_GAP = 120;
  
  const H_X_GAP = 360; 
  const H_Y_GAP = 250; 

  let x, y;

  if (layout === 'vertical') {
      x = depth * V_X_GAP + 80;
      y = startOffset * V_Y_GAP + 80;
  } else {
      x = startOffset * H_X_GAP + 80;
      y = depth * H_Y_GAP + 80;
  }
  
  const node: GraphNode = {
    id: nodeId,
    type: isArray ? 'array' : 'object',
    path: path,
    x,
    y,
    data: {},
    label: path.split('.').pop() || path.split('[').pop()?.replace(']', '') || 'Root',
    totalSize: myTreeSize 
  };

  let currentOffsetCursor = startOffset;
  
  keys.forEach((key) => {
    const value = data[key];
    const currentPath = path ? (isArray ? `${path}[${key}]` : `${path}.${key}`) : key;
    const isPrimitive = value === null || typeof value !== 'object';

    if (isPrimitive) {
      node.data[key] = value;
    } else {
      const childResult = processGraph(value, layout, currentPath, depth + 1, currentOffsetCursor);
      nodes.push(...childResult.nodes);
      edges.push(...childResult.edges);
      edges.push({ from: nodeId, to: currentPath, label: key });

      currentOffsetCursor += childResult.size + (layout === 'vertical' ? 1.2 : 0.2);
    }
  });

  const totalSizeUsed = Math.max(1, currentOffsetCursor - startOffset);
  nodes.push(node);
  
  return { nodes, edges, size: totalSizeUsed };
};

// --- Components ---

// Helper for editing values
const EditableValue: React.FC<{ value: any, onCommit: (val: any) => void, className?: string }> = ({ value, onCommit, className }) => {
  const [localValue, setLocalValue] = useState(String(value === null ? 'null' : value));
  const [isEditing, setIsEditing] = useState(false);

  useEffect(() => {
    if (!isEditing) {
       setLocalValue(String(value === null ? 'null' : value));
    }
  }, [value, isEditing]);

  const handleBlur = () => {
    setIsEditing(false);
    let finalVal: any = localValue;
    
    // Simple inference
    if (localValue === 'true') finalVal = true;
    else if (localValue === 'false') finalVal = false;
    else if (localValue === 'null') finalVal = null;
    else if (!isNaN(Number(localValue)) && localValue.trim() !== '') {
       finalVal = Number(localValue);
    }
    
    if (finalVal !== value) {
      onCommit(finalVal);
    }
  };

  const handleKeyDown = (e: React.KeyboardEvent) => {
    if (e.key === 'Enter') {
      (e.target as HTMLInputElement).blur();
    }
  };

  let colorClass = 'text-emerald-400';
  if (typeof value === 'number') colorClass = 'text-blue-400';
  if (typeof value === 'boolean') colorClass = 'text-purple-400';
  if (value === null) colorClass = 'text-gray-500';

  return (
    <input
      value={localValue}
      onChange={(e) => setLocalValue(e.target.value)}
      onFocus={() => setIsEditing(true)}
      onBlur={handleBlur}
      onKeyDown={handleKeyDown}
      // STOP PROPAGATION: This prevents the drag handler from stealing the click
      onMouseDown={(e) => e.stopPropagation()}
      className={`bg-transparent border-none outline-none min-w-[20px] ${colorClass} focus:ring-1 focus:ring-blue-500/50 rounded px-1 -ml-1 transition-all ${className || ''}`}
    />
  );
};

interface GraphNodeProps {
  node: GraphNode;
  onCopyPath: (path: string) => void;
  onMouseDown: (e: React.MouseEvent, nodeId: string) => void;
  onEdit: (path: string, key: string, newValue: any) => void;
}

const GraphNodeComponent: React.FC<GraphNodeProps> = ({ node, onCopyPath, onMouseDown, onEdit }) => {
  const isArray = node.type === 'array';
  
  return (
    <div 
      className="absolute bg-slate-900 border border-slate-700 rounded-lg shadow-xl overflow-hidden hover:border-blue-500/50 transition-colors w-80 group cursor-grab active:cursor-grabbing z-10"
      style={{ 
        left: node.x, 
        top: node.y,
        transform: 'translate(0, 0)' // Handled by left/top now for easier dragging logic
      }}
      onClick={(e) => {
        e.stopPropagation();
        onCopyPath(node.path);
      }}
      onMouseDown={(e) => {
        e.stopPropagation();
        onMouseDown(e, node.id);
      }}
    >
      {/* Header */}
      <div className={`px-4 py-3 text-sm font-bold uppercase tracking-wider flex justify-between items-center
        ${isArray ? 'bg-purple-900/30 text-purple-300' : 'bg-blue-900/30 text-blue-300'}
      `}>
        <div className="flex items-center truncate" title={node.path}>
          {isArray ? <Braces size={16} className="mr-2" /> : <Network size={16} className="mr-2" />}
          <span className="truncate max-w-[180px]">{node.label}</span>
        </div>
        <div className="flex items-center space-x-2">
           <Move size={12} className="text-slate-500 opacity-50" />
           <span className="opacity-0 group-hover:opacity-100 transition-opacity text-[10px] bg-slate-950 px-1 rounded text-slate-500">
            Copy Path
          </span>
        </div>
      </div>

      {/* Body (Primitives) */}
      <div className="p-3 space-y-1.5">
        {Object.keys(node.data).length === 0 ? (
          <div className="text-slate-600 text-sm italic px-1">Contains objects...</div>
        ) : (
          Object.entries(node.data).map(([k, v]) => (
            <div key={k} className="flex items-center text-sm font-mono border-b border-slate-800/50 last:border-0 pb-1.5 mb-1.5 last:pb-0 last:mb-0">
              <span className="text-slate-400 mr-2 shrink-0 select-none">{k}:</span>
              <div className="flex-1 min-w-0">
                <EditableValue 
                  value={v} 
                  onCommit={(newValue) => onEdit(node.path, k, newValue)} 
                />
              </div>
            </div>
          ))
        )}
      </div>
    </div>
  );
};

interface GraphEdgeProps {
  startX: number;
  startY: number;
  endX: number;
  endY: number;
  label: string;
  layout: 'vertical' | 'horizontal';
}

const GraphEdge: React.FC<GraphEdgeProps> = ({ startX, startY, endX, endY, label, layout }) => {
  // Bezier curve logic
  let sX, sY, eX, eY, c1x, c1y, c2x, c2y;

  if (layout === 'vertical') {
      sX = startX + 320; 
      sY = startY + 28; 
      eX = endX;
      eY = endY + 28; 
      c1x = sX + (eX - sX) / 2;
      c1y = sY;
      c2x = eX - (eX - sX) / 2;
      c2y = eY;
  } else {
      sX = startX + 160; 
      sY = startY + 60; // Approx bottom
      eX = endX + 160; // Center top
      eY = endY;
      
      c1x = sX;
      c1y = sY + (eY - sY) / 2;
      c2x = eX;
      c2y = eY - (eY - sY) / 2;
  }

  const pathData = `M ${sX} ${sY} C ${c1x} ${c1y}, ${c2x} ${c2y}, ${eX} ${eY}`;

  return (
    <g>
      <path 
        d={pathData} 
        fill="none" 
        stroke="#334155" 
        strokeWidth="3" 
        className="opacity-50 transition-all duration-75"
      />
      <rect 
        x={(sX + eX) / 2 - (label.length * 4 + 12)} 
        y={(sY + eY) / 2 - 12} 
        width={label.length * 8 + 24} 
        height={24} 
        rx={6} 
        fill="#0f172a" 
        className="stroke-slate-800"
        strokeWidth={1.5}
      />
      <text 
        x={(sX + eX) / 2} 
        y={(sY + eY) / 2 + 5} 
        fill="#94a3b8" 
        textAnchor="middle" 
        fontSize="12"
        fontFamily="monospace"
        fontWeight="500"
      >
        {label}
      </text>
    </g>
  );
};

interface JsonNodeProps {
  itemKey?: string | number;
  value: any;
  isLast: boolean;
  path?: string;
  searchTerm?: string;
  onCopyPath: (path: string) => void;
  onEdit: (path: string, key: string, newValue: any) => void;
}

const JsonNode: React.FC<JsonNodeProps> = ({ 
  itemKey, 
  value, 
  isLast, 
  path = '', 
  searchTerm = '', 
  onCopyPath,
  onEdit
}) => {
  const [isExpanded, setIsExpanded] = useState(true);
  const [isHovered, setIsHovered] = useState(false);

  const isObject = value !== null && typeof value === 'object' && !Array.isArray(value);
  const isArray = Array.isArray(value);
  const isPrimitive = !isObject && !isArray;

  const currentPath = path 
    ? (Number.isInteger(itemKey) ? `${path}[${itemKey}]` : `${path}.${itemKey}`) 
    : String(itemKey || '');

  const matchesSearch = (val: any, term: string) => {
    if (!term) return true;
    const s = JSON.stringify(val).toLowerCase();
    const t = term.toLowerCase();
    return s.includes(t);
  };

  if (searchTerm && !matchesSearch(value, searchTerm) && !matchesSearch(itemKey, searchTerm)) {
    return null;
  }

  const handleCopyPath = (e: React.MouseEvent) => {
    e.stopPropagation();
    onCopyPath(currentPath);
  };

  if (isPrimitive) {
    // Determine parent path and key for editing
    // currentPath is the full path to this item.
    // We need to split it to call onEdit(parentPath, key, val)
    // However, onEdit expects (path_to_object, key_in_object, value)
    
    // Logic to split currentPath into parent and key:
    // "team.leads[0]" -> parent: "team.leads", key: "0"
    // "project" -> parent: "", key: "project"
    
    const splitPath = (fullPath: string) => {
        const lastDot = fullPath.lastIndexOf('.');
        const lastBracket = fullPath.lastIndexOf('[');
        
        if (lastBracket > lastDot) {
           // Array item: "obj.arr[0]"
           const parent = fullPath.substring(0, lastBracket);
           const key = fullPath.substring(lastBracket + 1, fullPath.length - 1);
           return { parent, key };
        } else if (lastDot > -1) {
           // Object item: "obj.key"
           const parent = fullPath.substring(0, lastDot);
           const key = fullPath.substring(lastDot + 1);
           return { parent, key };
        } else {
           // Root item: "key"
           return { parent: '', key: fullPath };
        }
    };

    const { parent, key } = splitPath(currentPath);

    return (
      <div 
        className={`group flex items-center font-mono text-sm hover:bg-slate-800/50 rounded px-1 py-0.5 cursor-pointer transition-colors`}
        onMouseEnter={() => setIsHovered(true)}
        onMouseLeave={() => setIsHovered(false)}
        onClick={handleCopyPath}
      >
        {itemKey !== undefined && (
          <span className="text-slate-400 mr-2 opacity-90">{itemKey}:</span>
        )}
        <EditableValue 
            value={value} 
            onCommit={(newVal) => onEdit(parent, key, newVal)}
            className="break-all"
        />
        {!isLast && <span className="text-slate-500">,</span>}
        
        {isHovered && (
          <span className="ml-2 text-xs text-slate-500 bg-slate-900 px-2 py-0.5 rounded border border-slate-700 opacity-0 group-hover:opacity-100 transition-opacity">
            Click to copy path
          </span>
        )}
      </div>
    );
  }

  const keys = Object.keys(value);
  const brackets = isArray ? ['[', ']'] : ['{', '}'];

  return (
    <div className="font-mono text-sm">
      <div 
        className="flex items-center hover:bg-slate-800/50 rounded px-1 py-0.5 cursor-pointer"
        onClick={() => setIsExpanded(!isExpanded)}
      >
        <button className="mr-1 text-slate-500 hover:text-white transition-colors">
          {isExpanded ? <ChevronDown size={14} /> : <ChevronRight size={14} />}
        </button>
        
        {itemKey !== undefined && (
          <span className="text-slate-300 mr-2 font-semibold">{itemKey}:</span>
        )}
        
        <span className="text-yellow-500 font-bold">{brackets[0]}</span>
        
        {!isExpanded && (
          <span className="text-slate-500 mx-2 text-xs italic">
             {isArray ? `${keys.length} items` : `${keys.length} keys`} 
          </span>
        )}

        {!isExpanded && (
          <>
            <span className="text-yellow-500 font-bold">{brackets[1]}</span>
            {!isLast && <span className="text-slate-500">,</span>}
          </>
        )}
      </div>

      {isExpanded && (
        <div className="pl-4 border-l border-slate-700/50 ml-2.5">
          {keys.map((key, idx) => (
            <JsonNode
              key={key}
              itemKey={isArray ? parseInt(key) : key}
              value={value[key]}
              isLast={idx === keys.length - 1}
              path={currentPath}
              searchTerm={searchTerm}
              onCopyPath={onCopyPath}
              onEdit={onEdit}
            />
          ))}
        </div>
      )}
      
      {isExpanded && (
        <div className="pl-1">
          <span className="text-yellow-500 font-bold">{brackets[1]}</span>
          {!isLast && <span className="text-slate-500">,</span>}
        </div>
      )}
    </div>
  );
};

// --- Main Application Component ---

interface OpenDoc {
  filename: string;
  content: string;
  originalContent: string;
}

export default function JsonVisualizer() {
  const [files, setFiles] = useState<string[]>([]);
  const [openDocs, setOpenDocs] = useState<OpenDoc[]>([]);
  const [activeDocIndex, setActiveDocIndex] = useState<number>(-1);
  const [input, setInput] = useState('');
  const [parsedData, setParsedData] = useState<any>(null);
  const [error, setError] = useState<string | null>(null);
  const [searchTerm, setSearchTerm] = useState('');
  const [notification, setNotification] = useState<{msg: string; isError?: boolean} | null>(null);
  const [viewMode, setViewMode] = useState<'split' | 'editor' | 'visual' | 'graph'>('graph');
  const [isDragging, setIsDragging] = useState(false);
  const [jsonPath, setJsonPath] = useState('');
  const [jsonPathResult, setJsonPathResult] = useState<any>(null);
  const [layoutMode, setLayoutMode] = useState<'vertical' | 'horizontal'>('vertical');
  const fileInputRef = useRef<HTMLInputElement>(null);

  // File System Access API State
  const [dirHandle, setDirHandle] = useState<any>(null);
  const fileHandles = useRef<Record<string, any>>({});

  // Auto-save state
  const [isSaving, setIsSaving] = useState(false);
  const debouncedInput = useDebounce(input, 1000); // 1s delay for auto-save

  // Graph Data State
  const [graphData, setGraphData] = useState<{ nodes: GraphNode[]; edges: GraphEdge[] }>({ nodes: [], edges: [] });

  // --- Movement State ---
  const [pan, setPan] = useState({ x: 0, y: 0 });
  const [scale, setScale] = useState(1);
  const [isDraggingCanvas, setIsDraggingCanvas] = useState(false);
  const [draggedNodeId, setDraggedNodeId] = useState<string | null>(null);
  
  const dragStartRef = useRef({ x: 0, y: 0 });
  const itemStartRef = useRef({ x: 0, y: 0 });
  
  const transformLayerRef = useRef<HTMLDivElement>(null);
  const zoomTimeoutRef = useRef<any>(null);

  // Refs for smooth event handling without re-binding
  const panRef = useRef(pan);
  const scaleRef = useRef(scale);

  // Sync refs with state
  useEffect(() => { panRef.current = pan; }, [pan]);
  useEffect(() => { scaleRef.current = scale; }, [scale]);

  const previousGraphNode = useRef<HTMLDivElement | null>(null);

  // --- Wheel / Zoom Logic via Callback Ref ---
  const setGraphRef = React.useCallback((node: HTMLDivElement | null) => {
    // Cleanup previous listener if node changed
    if (previousGraphNode.current) {
       previousGraphNode.current.removeEventListener('wheel', onWheelRef.current);
    }

    if (node) {
       node.addEventListener('wheel', onWheelRef.current, { passive: false });
    }
    
    previousGraphNode.current = node;
  }, []);

  // Stable event handler ref to avoid re-binding
  const onWheelRef = useRef((e: WheelEvent) => {
      e.preventDefault();

      const currentScale = scaleRef.current;
      const currentPan = panRef.current;
      const container = e.currentTarget as HTMLDivElement;

      let newScale = currentScale;
      let newPan = { ...currentPan };

      if (e.ctrlKey || e.metaKey) {
        // Zoom (Pinch)
        const zoomSensitivity = 0.002; 
        const delta = -e.deltaY * zoomSensitivity;
        newScale = Math.min(Math.max(0.1, currentScale + delta), 5);

        const rect = container.getBoundingClientRect();
        const mouseX = e.clientX - rect.left;
        const mouseY = e.clientY - rect.top;

        const worldX = (mouseX - currentPan.x) / currentScale;
        const worldY = (mouseY - currentPan.y) / currentScale;

        newPan.x = mouseX - worldX * newScale;
        newPan.y = mouseY - worldY * newScale;
      } else {
        // Pan
        const damping = 1; 
        newPan.x = currentPan.x - e.deltaX * damping;
        newPan.y = currentPan.y - e.deltaY * damping;
      }

      // 1. Update Refs immediately (source of truth for next event)
      scaleRef.current = newScale;
      panRef.current = newPan;

      // 2. Direct DOM update (Bypass React Render)
      if (transformLayerRef.current) {
          transformLayerRef.current.style.transform = `translate(${newPan.x}px, ${newPan.y}px) scale(${newScale})`;
          transformLayerRef.current.style.transformOrigin = '0 0';
      }

      // 3. Debounce React State update (Sync eventually)
      if (zoomTimeoutRef.current) clearTimeout(zoomTimeoutRef.current);
      zoomTimeoutRef.current = setTimeout(() => {
          // Only update if changed significantly to avoid minor jitters or redundant renders
          // But here we just sync.
          ReactDOM.flushSync(() => {
             setScale(newScale);
             setPan(newPan);
          });
      }, 150);
  });

  const [sidebarWidth, setSidebarWidth] = useState(256);
  const [isResizingSidebar, setIsResizingSidebar] = useState(false);

  // --- Sidebar Resize Logic ---
  useEffect(() => {
    if (!isResizingSidebar) return;

    const handleMouseMove = (e: MouseEvent) => {
      const newWidth = Math.max(150, Math.min(e.clientX, 600));
      setSidebarWidth(newWidth);
    };

    const handleMouseUp = () => {
      setIsResizingSidebar(false);
      document.body.style.cursor = 'default';
    };

    document.addEventListener('mousemove', handleMouseMove);
    document.addEventListener('mouseup', handleMouseUp);
    document.body.style.cursor = 'col-resize';

    return () => {
      document.removeEventListener('mousemove', handleMouseMove);
      document.removeEventListener('mouseup', handleMouseUp);
      document.body.style.cursor = 'default';
    };
  }, [isResizingSidebar]);

  // --- File System Access Logic ---

  const showNotification = (msg: string, isError = false) => {
    setNotification({ msg, isError });
    setTimeout(() => setNotification(null), 3000);
  };

  const handleOpenFolder = async () => {
    try {
      // @ts-ignore - showDirectoryPicker is not yet in all TS defs
      const handle = await window.showDirectoryPicker({
        mode: 'readwrite'
      });
      
      setDirHandle(handle);
      await refreshFileList(handle);
      showNotification("Folder opened");
    } catch (err) {
      console.error(err);
      // User probably cancelled
    }
  };

  const refreshFileList = async (handle: any) => {
    const newFiles: string[] = [];
    fileHandles.current = {};

    const scanDirectory = async (dirHandle: any, pathPrefix: string, depth: number) => {
      if (depth > 4) return;

      for await (const entry of dirHandle.values()) {
        if (entry.kind === 'file' && entry.name.endsWith('.json')) {
          const filePath = pathPrefix + entry.name;
          newFiles.push(filePath);
          fileHandles.current[filePath] = entry;
        } else if (entry.kind === 'directory') {
          // Recursively scan subdirectories
          await scanDirectory(entry, pathPrefix + entry.name + '/', depth + 1);
        }
      }
    };

    await scanDirectory(handle, '', 1);
    setFiles(newFiles.sort());
  };

  const handleOpenFile = async (filename: string) => {
    const existingIndex = openDocs.findIndex(d => d.filename === filename);
    if (existingIndex >= 0) {
      setActiveDocIndex(existingIndex);
      return;
    }

    try {
      const handle = fileHandles.current[filename];
      if (!handle) throw new Error("File handle not found");

      const file = await handle.getFile();
      const text = await file.text();

      const newDoc = { filename, content: text, originalContent: text };
      setOpenDocs(prev => [...prev, newDoc]);
      setActiveDocIndex(openDocs.length);
    } catch (e) {
      showNotification("Failed to read file", true);
    }
  };

  const handleCloseTab = (e: React.MouseEvent, index: number) => {
    e.stopPropagation();
    setOpenDocs(prev => prev.filter((_, i) => i !== index));
    if (activeDocIndex >= index) {
      setActiveDocIndex(Math.max(0, activeDocIndex - 1));
    }
    if (openDocs.length === 1) {
      setActiveDocIndex(-1);
      setInput('');
      setParsedData(null);
    }
  };

  const handleSaveFile = async (contentToSave: string, silent = false) => {
    if (activeDocIndex === -1) return;
    const doc = openDocs[activeDocIndex];
    const handle = fileHandles.current[doc.filename];

    if (!handle) {
      if (!silent) showNotification("Cannot save: File handle lost", true);
      return;
    }
    
    setIsSaving(true);
    try {
      const writable = await handle.createWritable();
      await writable.write(contentToSave);
      await writable.close();

      setOpenDocs(prev => prev.map((d, i) => i === activeDocIndex ? { ...d, originalContent: contentToSave } : d));
      if (!silent) showNotification(`Saved ${doc.filename}`);
    } catch (e) {
      console.error(e);
      if (!silent) showNotification("Save error", true);
    } finally {
      setIsSaving(false);
    }
  };

  // Sync active doc to input
  useEffect(() => {
    if (activeDocIndex >= 0 && openDocs[activeDocIndex]) {
      setInput(openDocs[activeDocIndex].content);
    } else if (activeDocIndex === -1) {
      setInput('');
      setParsedData(null);
    }
  }, [activeDocIndex]); 

  // Auto-Save Effect
  useEffect(() => {
     if (activeDocIndex !== -1 && openDocs[activeDocIndex]) {
        const doc = openDocs[activeDocIndex];
        // Only save if content is different and valid JSON
        if (debouncedInput !== doc.originalContent && !error) {
            handleSaveFile(debouncedInput, true);
        }
     }
  }, [debouncedInput]);


  // Parse Input Effect
  useEffect(() => {
    try {
      if (!input.trim()) {
        setParsedData(null);
        setError(null);
        return;
      }
      const parsed = JSON.parse(input);
      setParsedData(parsed);
      setError(null);
      
      if (parsed && !draggedNodeId) {
        const { nodes, edges } = processGraph(parsed, layoutMode);
        setGraphData({ nodes, edges });
      }
    } catch (err: any) {
      setError(err.message);
    }
  }, [input, layoutMode]); 

  // --- Drag Handlers ---
  const handleMouseDown = (e: React.MouseEvent, nodeId: string | null = null) => {
    if (e.button !== 0) return;
    e.preventDefault();
    dragStartRef.current = { x: e.clientX, y: e.clientY };
    
    if (nodeId) {
      setDraggedNodeId(nodeId);
      const node = graphData.nodes.find(n => n.id === nodeId);
      if (node) itemStartRef.current = { x: node.x, y: node.y };
    } else {
      setIsDraggingCanvas(true);
      itemStartRef.current = { x: pan.x, y: pan.y };
    }
  };

  const handleMouseMove = (e: MouseEvent) => {
    if (isDraggingCanvas) {
      const dx = e.clientX - dragStartRef.current.x;
      const dy = e.clientY - dragStartRef.current.y;
      
      const currentPan = itemStartRef.current; // Stored at drag start
      const newPan = { x: currentPan.x + dx, y: currentPan.y + dy };
      const currentScale = scaleRef.current;

      // 1. Update Ref
      panRef.current = newPan;

      // 2. Direct DOM
      if (transformLayerRef.current) {
          transformLayerRef.current.style.transform = `translate(${newPan.x}px, ${newPan.y}px) scale(${currentScale})`;
          transformLayerRef.current.style.transformOrigin = '0 0';
      }

      // 3. Debounce State
      if (zoomTimeoutRef.current) clearTimeout(zoomTimeoutRef.current);
      zoomTimeoutRef.current = setTimeout(() => {
          setPan(newPan);
      }, 150);

    } else if (draggedNodeId) {
      // Scale correction for dragging nodes
      const currentScale = scaleRef.current;
      const dx = (e.clientX - dragStartRef.current.x) / currentScale;
      const dy = (e.clientY - dragStartRef.current.y) / currentScale;
      
      setGraphData(prev => ({
        ...prev,
        nodes: prev.nodes.map(n => 
          n.id === draggedNodeId 
            ? { ...n, x: itemStartRef.current.x + dx, y: itemStartRef.current.y + dy }
            : n
        )
      }));
    }
  };

  const handleMouseUp = () => {
    setIsDraggingCanvas(false);
    setDraggedNodeId(null);
  };

  useEffect(() => {
    if (isDraggingCanvas || draggedNodeId) {
      window.addEventListener('mousemove', handleMouseMove);
      window.addEventListener('mouseup', handleMouseUp);
    } else {
      window.removeEventListener('mousemove', handleMouseMove);
      window.removeEventListener('mouseup', handleMouseUp);
    }
    return () => {
      window.removeEventListener('mousemove', handleMouseMove);
      window.removeEventListener('mouseup', handleMouseUp);
    };
  }, [isDraggingCanvas, draggedNodeId, graphData.nodes]);

  // --- Actions ---
  const handleFormat = () => {
    try {
      const parsed = JSON.parse(input);
      setInput(JSON.stringify(parsed, null, 2));
      showNotification("Formatted JSON");
    } catch (e) {
      showNotification("Cannot format: Invalid JSON", true);
    }
  };

  const handleMinify = () => {
    try {
      const parsed = JSON.parse(input);
      setInput(JSON.stringify(parsed));
      showNotification("Minified JSON");
    } catch (e) {
      showNotification("Cannot minify: Invalid JSON", true);
    }
  };

  const handleClear = () => {
    setInput('');
    setParsedData(null);
  };

  const handleCopyInput = () => {
    navigator.clipboard.writeText(input);
    showNotification("Raw JSON copied");
  };

  const handleCopyPath = (path: string) => {
    navigator.clipboard.writeText(path);
    showNotification(`Path copied: ${path}`);
  };

  const evaluateJSONPath = (path: string) => {
    if (!path.trim() || !parsedData) {
      setJsonPathResult(null);
      return;
    }
    try {
      let result = parsedData;
      const parts = path.replace(/^\$\.?/, '').split(/\.|\[|\]/).filter(p => p);
      for (const part of parts) {
        if (result === null || result === undefined) break;
        result = result[part];
      }
      setJsonPathResult(result);
      showNotification(`JSONPath evaluated`);
    } catch (err) {
      setJsonPathResult(null);
      showNotification("Invalid JSONPath", true);
    }
  };

  const handleNodeEdit = (path: string, key: string, newValue: any) => {
    if (!parsedData) return;
    try {
      const updatedData = setValueByPath(parsedData, path, key, newValue);
      const newContent = JSON.stringify(updatedData, null, 2);
      setInput(newContent);
      // Also update the openDocs state so switching tabs doesn't lose it
      if (activeDocIndex >= 0) {
         setOpenDocs(prev => prev.map((d, i) => i === activeDocIndex ? { ...d, content: newContent } : d));
      }
      // We don't save immediately; let useDebounce handle it
      showNotification(`Updated ${key}`);
    } catch (e) {
      showNotification("Failed to update value", true);
    }
  };

  // Drag and Drop (Modified to load into new tab? Or replace active?)
  // For simplicity: replace active or create new "Untitled" (but we need filename for saving)
  // Let's just disable drag-drop file loading for now or map it to "Imported"
  const handleDragOver = (e: React.DragEvent) => { e.preventDefault(); setIsDragging(true); };
  const handleDragLeave = (e: React.DragEvent) => { e.preventDefault(); setIsDragging(false); };
  const handleDrop = (e: React.DragEvent) => {
    e.preventDefault();
    setIsDragging(false);
    // File upload logic omitted for brevity/focus on jsons folder
  };


  return (
    <div className="min-h-screen bg-slate-950 text-slate-200 flex flex-col font-sans h-screen overflow-hidden">
      
      {/* --- Header --- */}
      <header className="bg-slate-900 border-b border-slate-800 h-14 flex items-center justify-between px-4 shrink-0">
        <div className="flex items-center space-x-2">
          <div className="bg-blue-600 p-1.5 rounded-lg">
            <Braces className="text-white" size={18} />
          </div>
          <h1 className="font-bold tracking-tight text-white">JSON Vision</h1>
        </div>

        {/* Center: Tabs */}
        <div className="flex-1 mx-4 overflow-x-auto no-scrollbar flex items-center space-x-1">
          {openDocs.map((doc, idx) => (
            <div 
              key={`${doc.filename}-${idx}`}
              className={`
                flex items-center space-x-2 px-3 py-1.5 rounded-t-lg text-xs border-t border-x cursor-pointer select-none min-w-[100px] max-w-[200px]
                ${activeDocIndex === idx 
                  ? 'bg-slate-800 border-slate-700 text-white' 
                  : 'bg-slate-900 border-transparent text-slate-500 hover:bg-slate-800/50'}
              `}
              onClick={() => setActiveDocIndex(idx)}
            >
              <FileText size={12} className={activeDocIndex === idx ? 'text-blue-400' : ''} />
              <span className="truncate flex-1">{doc.filename}</span>
              {doc.content !== doc.originalContent && !isSaving && (
                <span className="w-1.5 h-1.5 rounded-full bg-yellow-500"></span>
              )}
              {isSaving && activeDocIndex === idx && (
                <RefreshCw size={10} className="animate-spin text-emerald-400" />
              )}
              <button 
                onClick={(e) => handleCloseTab(e, idx)}
                className="hover:bg-slate-700 rounded p-0.5"
              >
                <X size={12} />
              </button>
            </div>
          ))}
        </div>

        <div className="flex items-center space-x-2">
           {/* Manual Save Button (Optional now with Auto-Save) */}
          <button 
            onClick={() => handleSaveFile(input)}
            disabled={activeDocIndex === -1}
            className={`flex items-center space-x-2 px-3 py-1.5 rounded text-xs font-medium transition-colors
              ${activeDocIndex !== -1 ? 'bg-blue-600 hover:bg-blue-700 text-white' : 'bg-slate-800 text-slate-500 cursor-not-allowed'}
            `}
          >
            <Save size={14} />
            <span className="hidden sm:inline">Save</span>
          </button>
        </div>
      </header>

      {/* --- Main Content Area --- */}
      <div className="flex-1 flex overflow-hidden">
        
        {/* Sidebar: File Explorer */}
        <aside 
          style={{ width: sidebarWidth }} 
          className="bg-slate-900 border-r border-slate-800 flex flex-col shrink-0 relative group"
        >
          <div className="p-3 border-b border-slate-800 flex items-center justify-between">
            <span className="text-xs font-bold uppercase text-slate-400 tracking-wider">JSON Files</span>
            <button onClick={handleOpenFolder} className="text-blue-400 hover:text-blue-300 p-1 rounded hover:bg-slate-800 flex items-center space-x-1 transition-colors" title="Open Local Folder">
              <Folder size={12} />
              <span className="text-[10px]">Open</span>
            </button>
          </div>
          <div className="flex-1 overflow-y-auto p-2 space-y-1">
            {files.length === 0 && (
               <div className="flex flex-col items-center justify-center py-8 text-slate-600 space-y-2">
                 <Folder size={24} className="opacity-50" />
                 <div className="text-xs text-center px-4">
                    Click &quot;Open" to select your <span className="font-mono text-slate-400">jsons/</span> folder
                 </div>
               </div>
            )}
            {files.map(file => (
              <div 
                key={file}
                onClick={() => handleOpenFile(file)}
                className={`
                  flex items-center space-x-2 px-2 py-1.5 rounded cursor-pointer text-sm group
                  ${openDocs.some(d => d.filename === file) ? 'text-blue-300' : 'text-slate-400 hover:text-slate-200 hover:bg-slate-800'}
                `}
              >
                <FileJson size={14} className="group-hover:text-blue-400" />
                <span className="truncate">{file}</span>
              </div>
            ))}
          </div>
          
          {/* Resize Handle */}
          <div 
            className="absolute top-0 right-0 w-1 h-full cursor-col-resize hover:bg-blue-500/50 transition-colors z-50"
            onMouseDown={() => setIsResizingSidebar(true)}
          />
        </aside>

        {/* Editor / Visualizer Split */}
        <main className="flex-1 flex overflow-hidden relative">
          
          {activeDocIndex === -1 ? (
             <div className="w-full h-full flex flex-col items-center justify-center text-slate-600 bg-slate-950">
                <Folder size={64} className="mb-4 opacity-20" />
                <p className="text-lg font-medium">No file open</p>
                <p className="text-sm">Select a file from the sidebar to start editing</p>
             </div>
          ) : (
            <>
              {/* Left Panel: Input Editor */}
              <div className={`flex flex-col border-r border-slate-800 transition-all duration-300 
                ${(viewMode === 'visual' || viewMode === 'graph') ? 'w-0 overflow-hidden opacity-0' : viewMode === 'editor' ? 'w-full' : 'w-1/2'}
              `}
              >
                <div className="bg-slate-900/50 p-2 border-b border-slate-800 flex items-center justify-between shrink-0">
                  <div className="flex items-center space-x-2 text-xs text-slate-400 ml-2">
                    <Edit3 size={12} />
                    <span>Editor</span>
                  </div>
                  <div className="flex space-x-1">
                    <button onClick={handleFormat} className="p-1.5 hover:bg-slate-700 rounded text-slate-400 hover:text-blue-400"><Play size={14} className="rotate-90" /></button>
                    <button onClick={handleMinify} className="p-1.5 hover:bg-slate-700 rounded text-slate-400 hover:text-blue-400"><Minimize2 size={14} /></button>
                    <button onClick={handleCopyInput} className="p-1.5 hover:bg-slate-700 rounded text-slate-400 hover:text-emerald-400"><Copy size={14} /></button>
                  </div>
                </div>

                <div className="relative flex-1 h-full">
                   <textarea
                    value={input}
                    onChange={(e) => {
                      setInput(e.target.value);
                      // Update openDocs content immediately so it persists if we switch tabs
                      setOpenDocs(prev => prev.map((d, i) => i === activeDocIndex ? { ...d, content: e.target.value } : d));
                    }}
                    className="w-full h-full bg-slate-950 text-slate-300 font-mono text-sm p-4 resize-none focus:outline-none border-none"
                    spellCheck={false}
                  />
                  {error && (
                    <div className="absolute bottom-4 left-4 right-4 bg-red-900/90 border border-red-700 text-red-200 px-4 py-2 rounded text-sm backdrop-blur-sm flex items-center space-x-2">
                      <AlertCircle size={16} />
                      <span className="truncate">{error}</span>
                    </div>
                  )}
                </div>
              </div>

              {/* Right Panel: Visualizer */}
              <div className={`flex flex-col bg-slate-900/30 transition-all duration-300
                ${viewMode === 'editor' ? 'w-0 overflow-hidden opacity-0' : (viewMode === 'visual' || viewMode === 'graph') ? 'w-full' : 'w-1/2'}
              `}>
                {/* Toolbar */}
                <div className="bg-slate-900/50 p-2 border-b border-slate-800 flex items-center justify-between shrink-0">
                   <div className="flex bg-slate-800 rounded p-0.5">
                      <button onClick={() => setViewMode('split')} className={`px-2 py-0.5 text-[10px] rounded ${viewMode === 'split' ? 'bg-blue-600 text-white' : 'text-slate-400'}`}>Split</button>
                      <button onClick={() => setViewMode('graph')} className={`px-2 py-0.5 text-[10px] rounded ${viewMode === 'graph' ? 'bg-blue-600 text-white' : 'text-slate-400'}`}>Graph</button>
                      <button onClick={() => setViewMode('visual')} className={`px-2 py-0.5 text-[10px] rounded ${viewMode === 'visual' ? 'bg-blue-600 text-white' : 'text-slate-400'}`}>Tree</button>
                   </div>
                   {viewMode !== 'graph' && (
                     <input 
                        type="text" 
                        placeholder="Filter..." 
                        value={searchTerm}
                        onChange={(e) => setSearchTerm(e.target.value)}
                        className="bg-slate-950 border border-slate-700 rounded px-2 py-0.5 text-xs w-24 focus:w-32 transition-all outline-none text-slate-300"
                      />
                   )}
                </div>

                {/* Graph/Tree Area */}
                <div className="flex-1 overflow-hidden bg-slate-950 relative">
                  {!parsedData ? (
                     <div className="h-full flex flex-col items-center justify-center text-slate-600">
                        <p className="text-sm">Invalid JSON</p>
                     </div>
                  ) : viewMode === 'graph' ? (
                    <div 
                      ref={setGraphRef}
                      className={`w-full h-full relative overflow-hidden ${isDraggingCanvas ? 'cursor-grabbing' : 'cursor-grab'}`}
                      onMouseDown={(e) => handleMouseDown(e, null)}
                    >
                      {/* Graph Controls Overlay */}
                      <div className="absolute top-4 left-4 z-50 flex flex-col space-y-2">
                        <button 
                          onClick={(e) => { e.stopPropagation(); setLayoutMode(m => m === 'vertical' ? 'horizontal' : 'vertical'); }}
                          className="bg-slate-800 hover:bg-slate-700 text-white px-3 py-1.5 rounded shadow-lg border border-slate-700 text-xs font-medium transition-colors"
                        >
                          Layout: {layoutMode === 'vertical' ? 'Vertical' : 'Horizontal'}
                        </button>
                      </div>

                      {/* Watermark / Brand */}
                      <div className="absolute bottom-6 right-6 z-50 pointer-events-auto select-none flex flex-col items-end space-y-2">
                        <div className="flex items-center space-x-2 bg-slate-900/80 backdrop-blur-sm px-4 py-2 rounded-lg border border-slate-700/50 shadow-xl">
                          <div className="bg-gradient-to-br from-blue-600 to-purple-600 p-1.5 rounded">
                            <Braces className="text-white" size={16} />
                          </div>
                          <div className="text-sm">
                            <div className="font-bold text-white">JSON Vision</div>
                            <div className="text-[10px] text-slate-400">diegonmarcos.dev</div>
                          </div>
                        </div>
                        <a 
                          href="https://linktree.diegonmarcos.com" 
                          target="_blank"
                          rel="noopener noreferrer"
                          className="text-[10px] text-slate-500 hover:text-blue-400 transition-colors bg-slate-900/50 px-2 py-1 rounded"
                        >
                          linktree.diegonmarcos.com
                        </a>
                      </div>
                      
                      {/* Transform Layer */}
                      <div 
                        ref={transformLayerRef}
                        style={{ transform: `translate(${pan.x}px, ${pan.y}px) scale(${scale})`, transformOrigin: '0 0' }}
                        className="w-full h-full absolute top-0 left-0 will-change-transform"
                      >
                        <svg className="absolute top-0 left-0 w-[4000px] h-[4000px] pointer-events-none z-0 overflow-visible">
                          {graphData.edges.map((edge, idx) => {
                            const source = graphData.nodes.find(n => n.id === edge.from);
                            const target = graphData.nodes.find(n => n.id === edge.to);
                            if (!source || !target) return null;
                            return <GraphEdge key={idx} startX={source.x} startY={source.y} endX={target.x} endY={target.y} label={edge.label} layout={layoutMode} />;
                          })}
                        </svg>
                        {graphData.nodes.map(node => (
                          <GraphNodeComponent 
                            key={node.id} 
                            node={node} 
                            onCopyPath={handleCopyPath} 
                            onMouseDown={handleMouseDown}
                            onEdit={handleNodeEdit}
                          />
                        ))}
                      </div>
                    </div>
                  ) : (
                    <div className="p-4 overflow-auto h-full custom-scrollbar">
                      <JsonNode 
                        itemKey={undefined} 
                        value={parsedData} 
                        isLast={true} 
                        path="" 
                        searchTerm={searchTerm}
                        onCopyPath={handleCopyPath}
                        onEdit={handleNodeEdit}
                      />
                    </div>
                  )}
                </div>
              </div>
            </>
          )}
        </main>
      </div>

      {/* Notification Toast */}
      {notification && (
        <div className={`fixed bottom-6 right-6 px-4 py-2 rounded-lg shadow-xl backdrop-blur-md border flex items-center space-x-2 text-sm font-medium animate-in fade-in slide-in-from-bottom-2 z-50
          ${notification.isError ? 'bg-red-950/80 border-red-800 text-red-200' : 'bg-blue-950/80 border-blue-800 text-blue-200'}
        `}>
          {notification.isError ? <AlertCircle size={16} /> : <Check size={16} />}
          <span>{notification.msg}</span>
        </div>
      )}
    </div>
  );
}